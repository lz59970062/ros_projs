import cv2
import numpy as np
# 读取二值图像
img = cv2.imread('suoyinhua.jpg')
resized_img = cv2.resize(img, (404, 404))
# 将 BGR 图像转换为gray像
gray_img = cv2.cvtColor(resized_img, cv2.COLOR_RGB2GRAY)
gray_img[gray_img > 128] = 255
gray_img[gray_img < 128] = 0

# 将 BGR 图像转换为 RGB 图像
#rgb_img = cv2.cvtColor(resized_img, cv2.COLOR_BGR2RGB)

# 定义方格纸的行数和列数
L = 400
num_rows = 10
num_cols = 10

# 创建一个字典来存储节点
nodes = {}


def constrain(x, low, max):
    if x < low:
        return low
    elif x > max:
        return max
    else:
        return x


def has_wall(map, p1, p2):
    # 坐标转换成数组索引
    p1 += 2
    p2 += 2
    p1[0], p1[1] = constrain(p1[0], 0, 404), constrain(p1[1], 0, 404)
    p2[0], p2[1] = constrain(p2[0], 0, 404), constrain(p2[1], 0, 404)

    if p1[0] == p2[0] and p1[1] != p2[1]:
        if p1[1] > p2[1]:
            temp = p1[1]
            p1[1] = p2[1]
            p2[1] = temp
        area = map[p1[1]:p2[1], p1[0]]
        sum = np.sum(area)
        if sum > 500:
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

        if sum > 500:
            return True
        else:
            return False


# 循环遍历所有的方格，以数字方式为每个节点命名，并将其存储到字典中
for row in range(num_rows):
    for col in range(num_cols):
        node_name = row*num_cols + col + 1
        y = row * L//10 + L//20
        x = col * L//10 + L//20

        node_center = np.array([x, y])
        # 获取某个像素点的值
        qian = has_wall(gray_img, node_center.copy(),
                        node_center+np.array([L//10, 0]))
        hou = has_wall(gray_img, node_center.copy(),
                       node_center+np.array([-L//10, 0]))
        zuo = has_wall(gray_img, node_center.copy(),
                       node_center+np.array([0, L//10]))

        you = has_wall(gray_img, node_center.copy(),
                       node_center+np.array([0, -L//10]))

        #neibor=[row*num_cols + col+1 + 1,row*num_cols + col -1+ 1,(row+1)*num_cols + col + 1,(row+1)*num_cols + col + 1]
        if qian == 1:
            qianmian = -1
        else:
            qianmian = row*num_cols + col+1 + 1
        if hou == 1:
            houmian = -1
        else:
            houmian = row*num_cols + col - 1 + 1
        if zuo == 1:
            zuomian = -1
        else:
            zuomian = (row+1)*num_cols + col + 1
        if you == 1:
            youmian = -1
        else:
            youmian = (row+1)*num_cols + col + 1

        neibor = [qianmian, houmian, zuomian, youmian]
        nodes[node_name] = node_center, [
            not qian, not hou, not zuo, not you], neibor

# 打印出节点字典
print(nodes)
