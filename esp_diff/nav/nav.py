import cv2
import numpy as np

from sko.SA import SA_TSP
from time import perf_counter

# 读取二值图像
img = cv2.imread('suoyinhua.jpg')
resized_img = cv2.resize(img, (404, 404))
# 将 BGR 图像转换为gray像
gray_img = cv2.cvtColor(resized_img, cv2.COLOR_RGB2GRAY)
gray_img[gray_img > 128] = 255
gray_img[gray_img < 128] = 0
gray_img2=gray_img.copy()
from collections import deque

# 定义方格纸的行数和列数
L = 400
num_rows = 10
num_cols = 10



def get_node(img, L, num_rows, num_cols,offsetx=2,offsety=2):
    # 创建一个字典来存储节点
    nodes = {}
    def constrain(x, low, max):
        if x < low:
            return low
        elif x > max:
            return max
        else:
            return x
    def valid(x, low, max):
        if x < low:
            return -1
        elif x > max:
            return -1
        else:
            return x
    def has_wall(map, p1, p2):
        # 坐标转换成数组索引
        p1 += offsetx
        p2 += offsety
        p1[0], p1[1] = constrain(p1[0], 0, 404), constrain(p1[1], 0, 404)
        p2[0], p2[1] = constrain(p2[0], 0, 404), constrain(p2[1], 0, 404)
        if p1[0] == p2[0] and p1[1] != p2[1]:
            if p1[1] > p2[1]:
                temp = p1[1]
                p1[1] = p2[1]
                p2[1] = temp
            area = map[p1[1]:p2[1], p1[0]]
            sum = np.sum(area)
            if sum > 1000:
                return True
            else:
                return False

        elif p1[0] != p2[0] and p1[1] == p2[1]:
            if p1[0] > p2[0]:
                temp = p1[0]
                p1[0] = p2[0]
                p2[0] = temp
            area = map[p1[1], p1[0]:p2[0]]
            sum = np.sum(area)

            if sum > 1000:
                return True
            else:
                return False


# 循环遍历所有的方格，以数字方式为每个节点命名，并将其存储到字典中
    for row in range(num_rows):
        for col in range(num_cols):
            node_name = row*num_cols + col
            cv2.putText(gray_img2, str(node_name), (col*L//10+15, row*L//10+23),(cv2.FONT_HERSHEY_SIMPLEX), 0.5, (200, 200,200), 1, cv2.LINE_AA)
            y = row * L//10 + L//20
            x = col * L//10 + L//20

            node_center = np.array([x, y])
            
            qian = has_wall(gray_img, node_center.copy(),
                            node_center+np.array([L//10, 0]))
            hou = has_wall(gray_img, node_center.copy(),
                           node_center+np.array([-L//10, 0]))
            zuo = has_wall(gray_img, node_center.copy(),
                           node_center+np.array([0, L//10]))
            you = has_wall(gray_img, node_center.copy(),
                           node_center+np.array([0, -L//10]))

            if qian == 1:
                qianmian = -1
            else:
                qianmian = row*num_cols + col+1 
            if hou == 1:
                houmian = -1
            else:
                houmian = row*num_cols + col - 1 
            if zuo == 1:
                zuomian = -1
            else:
                zuomian = (row+1)*num_cols + col 
            if you == 1:
                youmian = -1
            else:
                youmian = (row-1)*num_cols + col 
            
            neibor = [qianmian, houmian, zuomian, youmian]
            nei=[valid(i,0,num_rows*num_cols-1) for i in neibor]
            nodes[node_name] = node_center, [
                not qian, not hou, not zuo, not you], nei
    # 打印出节点字典
    cv2.imwrite("text3.jpg",gray_img2)
    return nodes 

class node():
    def __init__(self,id,data):
        pos,dir,available_node=data
        self.id=id
        self.pos=pos
        self.up=dir[0]
        self.forword=dir[1]
        self.left=dir[2]
        self.right=dir[3]
        self.available_node=[i for i in available_node if i!=-1]
    
    def __str__(self):
        return f"[id:{str(self.id)},pos:{str(self.pos)}]"
    def __repr__(self):
        return f"[id:{str(self.id)},pos:{str(self.pos)}]"
    def __eq__(self,other):
        return self.id==other.id
    def get_available_node(self):
        return self.available_node
    def get_pos(self):
        return self.pos

np.random.seed(0)
# for i,node in enumerate(nodes):
#     print(i,node.get_available_node())

def shortest_path(start, end, nodes):
    queue = deque([(start, [start])])
    visited = set([start])
    while queue:
        node, path = queue.popleft()
        if node == end:
            return path
        # print(node,path)
        for next_node in nodes[node].get_available_node():
            if next_node not in visited:
                queue.append((next_node, path + [next_node]))
                visited.add(next_node)
    return None

# path = shortest_path(start_node, end_node, nodes)
nodes=get_node(gray_img, L, num_rows, num_cols)
nodes=[node(i,nodes[i]) for i in nodes.keys()]
 
def path_len(start_node,end_node,nodes):
    path = shortest_path(start_node, end_node, nodes)
    if path is None:
        print("No path found")
        return np.nan
    else:
 
        return len(path)
        
def path_mat():
    mat=np.zeros((len(nodes),len(nodes)))
    for i in range(len(nodes)):
        for j in range(len(nodes)):
            mat[i,j]=path_len(i,j,nodes)
    return mat

def caculate_dis_mat(node_list):
    l=len(node_list)
    mat =np.zeros((l,l))
    for i in range(l):
        for j in range(l):
            mat[i,j]=path_len(node_list[i],node_list[j],nodes)
    return mat
 
def cal_total_distance(routine, distance_matrix):
    num_points, = routine.shape
    sum1 = 0
    sum1 += distance_matrix[-2, routine[0]]
    sum1 += distance_matrix[routine[-1], -1]
    return sum1+sum([distance_matrix[routine[i ], routine[(i + 1)  ]] for i in range(0, num_points - 1)])

# 退火算法TSP 问题
def path_planning(start_node, end_node, through_nodes, nodes):
    path_nodes = np.array(  through_nodes+[start_node]  + [end_node])
    print("path nodes",path_nodes)
    print(path_nodes)
    distance_matrix = caculate_dis_mat(path_nodes)
    points_coordinate = np.array([nodes[i].get_pos() for i in path_nodes])
    num_points = points_coordinate.shape[0]
    print("num_points",num_points)
  
    start=perf_counter()       
    # 执行模拟退火(SA)算法
    sa_tsp = SA_TSP(func=lambda x: cal_total_distance(x, distance_matrix), x0=range(num_points-2), T_max=1 , T_min=0.2 , L=2 * num_points)  #调用工具箱
    # 结果输出1
    best_points, best_distance = sa_tsp.run()
    print("运行时间是: {:.5f}s".format(perf_counter()-start))   #计时结束
    result_cur_best = [path_nodes[i] for i in best_points]
    print("最优路线：", result_cur_best)
    print("最优值：", cal_total_distance(best_points, distance_matrix))   #数据还原
    return [start_node]+result_cur_best+[end_node]

path=path_planning(0, 19, [12,49,18,27,90], nodes)
print(path)
 
 