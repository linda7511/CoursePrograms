import numpy as np
import matplotlib.pyplot as plt
from skimage import color, io, util

#将RGB图像转换为灰度图像，并计算图像的梯度作为能量图。
def energy_function(image):
    gray_image = color.rgb2gray(image)
    gradient = np.gradient(gray_image)
    return np.absolute(gradient[0]) + np.absolute(gradient[1])

#接收一张图像和对应的能量图作为输入，并计算出每个像素位置的累计成本和路径。
# 这里使用动态规划算法，从图像的顶部到底部计算每个像素位置的最小累计成本，并记录每个像素位置的路径。
def compute_cost(image, energy, axis=1):
    energy = energy.copy()

    if axis == 0:
        energy = np.transpose(energy, (1, 0))

    H, W = energy.shape

    cost = np.zeros((H, W))
    paths = np.zeros((H, W), dtype=np.int)#路径矩阵用于记录每个像素位置的路径选择（即上一行的路径索引-1/0/1.左上方/正上方/右上方）

    # Initialization
    cost[0] = energy[0]#将能量图的第一行赋值给成本矩阵的第一行
    paths[0] = 0#第一行的路径索引都设置为0


    #动态规划实现，方法一：循环嵌套
    for row in range(1, H):
        for j in range(0,W):
            if j == 0:
                cost[row][j] = min(cost[row-1][j], cost[row-1][j+1])+energy[row][j]
                paths[row][j] = np.argmin([cost[row-1][j], cost[row-1][j+1]])
            elif j == W-1:
                cost[row][j] = min(cost[row-1][j-1], cost[row-1][j]) + energy[row][j]
                paths[row][j] = np.argmin([cost[row-1][j-1], cost[row-1][j]])-1
            else:
                cost[row][j] = min(cost[row-1][j - 1], cost[row-1][j],cost[row-1][j+1]) + energy[row][j]
                paths[row][j] = np.argmin([cost[row-1][j - 1], cost[row-1][j], cost[row-1][j+1]]) - 1
    
    '''
    #方法二：借助numpy中的向量处理函数
    for row in range(1, H):
        upL = np.insert(cost[row - 1, 0:W - 1], 0, 1e10, axis=0)
        upM = cost[row - 1, :]
        upR = np.insert(cost[row - 1, 1:W], W - 1, 1e10, axis=0)
        upchoices = np.concatenate((upL, upM, upR), axis=0).reshape(3, -1)

        # M(i, j) = e(i, j) + min(M(i -1 , j - 1), M(i - 1, j), M(i - 1, j + 1))
        cost[row] = energy[row] + np.min(upchoices, axis=0)

        # left = -1
        # middle = 0
        # right = 1
        paths[row] = np.argmin(upchoices, axis=0) - 1
    '''


    if axis == 0:
        cost = np.transpose(cost, (1, 0))
        paths = np.transpose(paths, (1, 0))

    return cost, paths

#回溯最优路径
def backtrack_seam(paths, end):
    H, W = paths.shape
    seam = - np.ones(H, dtype=np.int)

    seam[H - 1] = end

    #自底向上回溯最优路径
    for h in range(H - 1, 0, -1):
        seam[h - 1] = seam[h] + paths[h, end]
        end += paths[h, end]

    return seam

#移除Seam
def remove_seam(image, seam):
    if len(image.shape) == 2:
        image = np.expand_dims(image, axis=2)

    H, W, C = image.shape

    mask = np.ones_like(image, bool)
    for h in range(H):
        mask[h, seam[h]] = False
    out = image[mask].reshape(H, W - 1, C)
    out = np.squeeze(out)

    return out

#缩小图像
def reduce(image, scaling, axis=1, efunc=energy_function, cfunc=compute_cost):
    out = np.copy(image)#创建图像副本
    if axis == 0:#表示要在垂直方向上进行缩小操作
        out = np.transpose(out, (1, 0, 2))

    while out.shape[1] > image.shape[1]*scaling:
        energy = efunc(out)#计算图像的能量图
        costs, paths = cfunc(out, energy)#计算图像每个像素位置的成本和路径
        end = np.argmin(costs[-1])#找到能量最小值路径的终点。
        seam = backtrack_seam(paths, end)
        out = remove_seam(out, seam)

    if axis == 0:
        out = np.transpose(out, (1, 0, 2))

    return out



#读取图像和展示结果
img = io.imread('imgs/SeamCarve_original.jpg')
img = util.img_as_float(img)
out = reduce(img, 0.5)

plt.subplot(1, 2, 1)
#plt.axis('off')  # 关闭坐标轴刻度

plt.subplot(1, 2, 2)
plt.imshow(out)
#plt.axis('off')  # 关闭坐标轴刻度

# 将out保存为PNG图像文件
output_path = 'out.png'
io.imsave(output_path, util.img_as_ubyte(out))

# 调整子图之间的间距
plt.tight_layout()
plt.show()