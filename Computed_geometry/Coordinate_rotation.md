坐标旋转主要要找到参考系，对于一个坐标，我们需要维护它与参考系之间的角度及长度比。 
坐标旋转公式 
对于任意两个不同点A和B,A绕B旋转ang角度的坐标为:

<a href="https://www.codecogs.com/eqnedit.php?latex=\left(\Delta&space;x\ast&space;cos\left(ang\right)-\Delta&space;y\ast&space;sin\left(ang\right)&plus;x_B,\Delta&space;y\ast&space;cos\left(ang\right)&plus;\Delta&space;x\ast&space;sin\left(ang\right)&plus;y_B\right)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\left(\Delta&space;x\ast&space;cos\left(ang\right)-\Delta&space;y\ast&space;sin\left(ang\right)&plus;x_B,\Delta&space;y\ast&space;cos\left(ang\right)&plus;\Delta&space;x\ast&space;sin\left(ang\right)&plus;y_B\right)" title="\left(\Delta x\ast cos\left(ang\right)-\Delta y\ast sin\left(ang\right)+x_B,\Delta y\ast cos\left(ang\right)+\Delta x\ast sin\left(ang\right)+y_B\right)" /></a>


