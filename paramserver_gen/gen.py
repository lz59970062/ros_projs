import os
import sys
import json


def gen_head_str(title):
    return'''<html>
<head>
    <meta charset='utf-8'>
    <meta name='viewport'
        content='width=device-width,initial-scale=1.0,maximum-scale=1.0,minimum-scale=1.0,user-scalable=no' />
    <title>%s</title>
    <style type='text/css'>
        a {color: black;text-decoration: none}
        nav {display: -webkit-box;-webkit-box-orient: horizontal;-webkit-box-pack: justify}
        .nav a {display: block}
        .mod {text-align: center;padding: 10px 0;border-top: 1px solid #EBEBEB}
        .mod .tab {margin: auto;width: 300px}
        .set {width: 90px}</style>
</head>
''' % (title)


def gen_param_line(name, value, page_name):
    return '''
    <td>%s</td><form action='%s.html' method='POST'><td><input type='text' class='set' name='%s' value=%s onchange='submit()'></td></form>''' % (name, page_name, value, '%'+value+'%')


def gen_param_block(block_name, name_list, value_list, page_name):
    str = '''<div class='mod'> <table class='tab'> <tr colspan='2'>%s</tr><tr>\n''' % (
        block_name)
    for i in range(len(name_list)):
        str += gen_param_line(name_list[i], value_list[i], page_name)
    str += '</tr></table></div>\n'
    return str


def gen_body_str(title, block_name_list, name_list, value_list, page_name, next_page):
    str = '''<body style='margin:0;padding:0'>
    <div style='background:#168DFD;text-align:center;line-height:45px'><span style='color: #fff'> %s</span></div>
    <div class='mod'>''' % (title)
    for i in range(len(block_name_list)):
        str += gen_param_block(block_name_list[i],
                               name_list[i], value_list[i], page_name)
    str += '</div>' + \
        "\n<p align='center'><a href='%s.html'>next page</a></p>" % (
            next_page)+'</body></html>'
    return str


def gen_page(title, block_name_list, name_list, value_list, page_name, next_page):
    str = gen_head_str(title)+gen_body_str(title, block_name_list,
                                           name_list, value_list, page_name, next_page)
    f = open(page_name+'.html', 'w')
    f.write(str)
    f.close()
    print('generate page %s.html' % (page_name))


def list_flatten(list):
    out_list = []
    for i in list:
        for j in i:
            out_list.append(j)
    return out_list


def gen_c_file(page_list, name_list, page_cnt, int_type, extern_func):
    name_list2 = name_list.copy()
    int_type2 = int_type.copy()

    int_type = []
    name_list = []
    for i in name_list2:
        for j in i:
            name_list.append(j)
    for i in int_type2:
        for j in i:
            int_type.append(j)
    type_str = "float "
    out_str = '#include "param.h"\n'
    for i in name_list2:
        
        out_str += type_str+' '
        for j in i:
            if j in int_type:
                continue
            out_str += j+","
        out_str = out_str[:-1]
        out_str += ';\n'

    type_str = "int "
    if len(int_type) != 0:
        int_type = list(set(int_type))
        out_str += type_str
    for i in int_type:
        out_str += ' '+i+','
    out_str = out_str[:-1]
    out_str += ';\n'
    for i in range(page_cnt):
        out_str += "const char *var_list"+str(i)+"[]={"
        for j in name_list2[i]:
            out_str += '"'+j+'",'
        out_str = out_str[:-1]
        out_str += "};\n"
    for i in range(page_cnt):
        out_str += "String processor_page"+str(i)+"(const String &var){\n"
        for j in range(len(name_list2[i])):
            if j == 0:
                out_str += "if(var==var_list"+str(i)+"["+str(j)+"]){\n"
                out_str += "return String("+name_list2[i][j]+",4);\n"
                out_str += "}\n"
            if name_list2[i][j] in int_type:
                out_str += "else if(var==var_list"+str(i)+"["+str(j)+"]){\n"
                out_str += "return String("+name_list2[i][j]+");\n"
                out_str += "}\n"
            else:
                out_str += "else if(var==var_list"+str(i)+"["+str(j)+"]){\n"
                out_str += "return String("+name_list2[i][j]+",4);\n"
                out_str += "}\n"
        out_str += "else return String();\n"
        out_str += "}\n"

    cnt = 0
    out_str += "void Param::begin_server(){\n"
    out_str += "  SPIFFS.begin();\n"
    out_str += '  AsyncWebServer::on("/", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS, "/%s.html", String(), false,%s);});\n' % (
        page_list[cnt], "processor_page"+str(cnt))
    while cnt < page_cnt:
        out_str += '  AsyncWebServer::on("/%s.html", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS,"/%s.html", String(), false,%s);});\n' % (
            page_list[cnt], page_list[cnt], "processor_page"+str(cnt))
        cnt += 1
    cnt = 0
    while cnt < page_cnt:
        out_str += '''  AsyncWebServer::on("/%s.html", HTTP_POST, [](AsyncWebServerRequest *request){
        int params = request->params();
        for (int i = 0; i < params; i++)
        {\nAsyncWebParameter *p = request->getParam(i);\nif (p->isPost())
            {''' % (page_list[cnt])
        for j in range(len(name_list2[cnt])):
            if j == 0:
                out_str += '  if(p->name()=="%s"){\n' % (name_list2[cnt][j])
                out_str += '    %s=p->value().toFloat();\n' % (
                    name_list2[cnt][j])
                out_str += '  }\n'
                continue
            if name_list2[cnt][j] in int_type:
                out_str += '  else if(p->name()=="%s"){\n' % (
                    name_list2[cnt][j])
                out_str += '    %s=p->value().toInt();\n' % (
                    name_list2[cnt][j])
                out_str += '  }\n'
            else:
                out_str += '  else if(p->name()=="%s"){\n' % (
                    name_list2[cnt][j])
                out_str += '    %s=p->value().toFloat();\n' % (
                    name_list2[cnt][j])
                out_str += '  }\n'
        out_str += '}}\nrequest->send(SPIFFS,"/%s.html", String(), false,%s);}); \n' % (
            page_list[cnt], "processor_page"+str(cnt))
        cnt += 1
    out_str += '''AsyncWebServer::begin();
    Serial.println("Server started at http://");
    Serial.println(WiFi.localIP());\n'''
    out_str += "}\n\n"
    if extern_func != None:
        extern_func = list_flatten(extern_func)

        for i in extern_func:
            if i != None and i != '':
                with open(i, 'r') as f:
                    out_str += f.read()

    return out_str


def unique(list):
    # order preserving
    checked = []
    for e in list:
        if e not in checked:
            checked.append(e)
    return checked


def paras_and_gen(file_list):
    c_name_list = []
    c_int_type = []
    c_page_list = []
    page_cnt = 0
    extern_func = []
    for json_file in file_list:

        f = open(json_file, 'r')
        json_str = f.read()
        f.close()
        json_dict = json.loads(json_str)
        title = json_dict['title']
        block_name_list = json_dict['block_name_list']
        name_list = json_dict['name_list']
        value_list = json_dict['value_list']
        page_name = json_dict['page_name']
        next_page = json_dict['next_page']
        int_type = json_dict["type_int"]
        extern_func.append(json_dict["func"])
        c_name_list.append(list_flatten(name_list))
        c_int_type.append(int_type)
        c_page_list.append(page_name)
        gen_page(title, block_name_list, name_list,
                 value_list, page_name, next_page)
        page_cnt += 1
    f = open('param.cpp', 'w')

    f.write(gen_c_file(c_page_list, unique(c_name_list),
            page_cnt, unique(c_int_type), extern_func))
    f.close()


file_list = os.listdir(".")
json_list = []
for i in file_list:
    if i.endswith('.json'):
        json_list.append(i)
print("json file list:")
print(json_list)


paras_and_gen(json_list)
# print(gen_head_str('test'))
