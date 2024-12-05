# 6.变换

我们可以尝试在每一帧重新计算顶点并且重新配置缓冲区来使其移动，但是这太繁琐了，而且会消耗非常多的处理时间。

因此我们可以使用矩阵`(Matrix`)对象来进行更好的变换

## 向量

向量有一个方向`Direction`和一个大小`Magnitude`。

![image-20241205141029452](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141029452.png)

为了让向量更为直观，我们通常设定方向的原点为(0,0,0)，然后指向一个方向，对应于一个点，使其变为位置向量。

### 向量与标量运算

标量`(Scalar)`只是一个数字（或者说是仅有一个分量的向量）。当把一个向量**加/减/乘/除**一个标量，我们可以简单的把**向量的每个分量分别进行该运算**。对于加法来说会像这样:

![image-20241205141206084](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141206084.png)

其中的+可以是+，-，·或÷，其中·是乘号。注意－和÷运算时不能颠倒（标量-/÷向量），因为颠倒的运算是没有定义的。

### 向量取反

我们在一个向量的每个分量前加负号就可以实现取反了（或者说用-1数乘该向量）

![image-20241205141252720](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141252720.png)

### 向量加减

向量的加法可以被定义为是分量的(Component-wise)相加，即将一个向量中的每一个分量加上另一个向量的对应分量：

![image-20241205141310260](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141310260.png)

向量的减法等于加上第二个向量的相反向量：

![image-20241205141415913](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141415913.png)

### 向量长度

我们使用勾股定理(Pythagoras Theorem)来获取向量的长度(Length)/大小(Magnitude)。如果你把向量的x与y分量画出来，该向量会和x与y分量为边形成一个三角形:

![image-20241205141446192](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141446192.png)

有一个特殊类型的向量叫做单位向量(Unit Vector)。单位向量有一个特别的性质——它的长度是1。我们可以用任意向量的每个分量除以向量的长度得到它的单位向量：

![image-20241205141718104](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141718104.png)

我们把这种方法叫做一个向量的标准化(Normalizing)。单位向量头上有一个^样子的记号。通常单位向量会变得很有用，特别是在我们只关心方向不关心长度的时候（如果改变向量的长度，它的方向并不会改变）。

### 向量乘法

#### 点乘

两个向量的点乘等于它们的数乘结果乘以两个向量之间夹角的余弦值。

![image-20241205141804276](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141804276.png)

点乘是通过将对应分量逐个相乘，然后再把所得积相加来计算的。

![image-20241205141818854](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141818854.png)

#### 叉乘

叉乘只在3D空间中有定义，它需要两个不平行向量作为输入，生成一个正交于两个输入向量的第三个向量。如果输入的两个向量也是正交的，那么叉乘之后将会产生3个互相正交的向量。接下来的教程中这会非常有用。下面的图片展示了3D空间中叉乘的样子：

![image-20241205141909297](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141909297.png)

![image-20241205141921667](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205141921667.png)

## 矩阵

#### 矩阵的加减

矩阵与标量之间的加减定义如下，一般数学上是没有矩阵的标量加减运算的。

![image-20241205142234151](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142234151.png)

矩阵与矩阵之间的加减就是两个矩阵对应元素的加减运算。

![image-20241205142312056](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142312056.png)

#### 矩阵的数乘

标量乘法和向量的计算方式一致

![image-20241205142328982](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142328982.png)

![image-20241205142445222](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142445222.png)

![image-20241205142507397](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142507397.png)

## 矩阵与向量相乘

其实向量就是一个N * 1的矩阵，因此如果我们有一个M * N的矩阵，就可以作用于我们的向量。

#### 单位矩阵

![image-20241205142547815](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142547815.png)

## 缩放

OpenGL的缩放操作通常是在3D空间进行操作的，对于2D的情况我们可以把z轴缩放1倍，这样z轴的值就不变了。

![image-20241205142811436](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142811436.png)

## 位移

![image-20241205142907811](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205142907811.png)

## 齐次坐标

向量的w分量也叫齐次坐标。想要从齐次向量得到3D向量，我们可以把x、y和z坐标分别除以w坐标。我们通常不会注意这个问题，因为w分量通常是1.0。使用齐次坐标有几点好处：它允许我们在3D向量上进行位移（如果没有w分量我们是不能位移向量的）

如果一个向量的齐次坐标是0，这个坐标就是方向向量(Direction Vector)，因为w坐标是0，这个向量就不能位移（译注：这也就是我们说的不能位移一个方向）。

## 旋转

2D或者3D空间中的旋转我们用**角`(Angle)`**来表示

大多数旋转函数需要用弧度制的角，角度制的角也可以很容易地转化为弧度制的：

- 弧度转角度：`角度 = 弧度 * (180.0f / PI)`
- 角度转弧度：`弧度 = 角度 * (PI / 180.0f)`

`PI`约等于3.14159265359。

在3D空间中旋转需要定义一个角和一个旋转轴，物体会沿着给定的旋转轴旋转特定的角度。

![image-20241205144932699](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205144932699.png)

下面这个公式，其中(Rx,Ry,Rz)代表任意旋转轴

![image-20241205145017124](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205145017124.png)

## 矩阵的组合

根据矩阵之间的乘法，我们可以把多个变换组合到一个矩阵中。让我们看看我们是否能生成一个变换矩阵，让它组合多个变换。假设我们有一个顶点(x, y, z)，我们希望将其缩放2倍，然后位移(1, 2, 3)个单位。我们需要一个位移和缩放矩阵来完成这些变换。结果的变换矩阵看起来像这样，在**最右边的矩阵是第一个与向量相乘**的，所以你应该从右向左读这个乘法。

![image-20241205145152907](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205145152907.png)

## GLM(OpenGL Mathematics)

注意我们现在使用的GLM版本是最新版本，当我们创建矩阵的时候，会默认全部初始化为零矩阵而不是单位矩阵，所以在创建矩阵的时候，我们都要进行初始化，赋值为单位矩阵。

```c++
glm::mat4 mat = glm::mat4(1.0f)
```

以下是我们所有需要用到的头文件

```c++
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

一个简单的小尝试，向量的位移将(1, 0, 0)位移(1, 1, 0)得到(2, 1, 0)。

`trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));`

这个translate居然不支持`vec4`，所以只能用`vec3`

```c++
glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
vec = trans * vec;
std::cout << vec.x << vec.y << vec.z << std::endl;
```

我们先用GLM内建的向量类定义一个叫做`vec`的向量。

接下来定义一个`mat4`类型的`trans`，默认是一个4×4单位矩阵。（注意我们当前使用的版本**默认初始化是零矩阵**）

下一步是创建一个变换矩阵，我们是把单位矩阵和一个位移向量传递给`glm::translate`函数来完成这个工作的（然后用给定的矩阵乘以位移矩阵就能获得最后需要的矩阵）。 

之后我们把向量乘以位移矩阵并且输出最后的结果。如果你仍记得位移矩阵是如何工作的话，得到的向量应该是(1 + 1, 0 + 1, 0 + 0)，也就是(2, 1, 0)。这个代码片段将会输出`210`，所以这个位移矩阵是正确的。

现在我们来针对之前的箱子来进行一个旋转和缩放变换

```c++
glm::mat4 trans;
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
```

注意，旋转的时候，GLM希望角度是弧度制的(radians)

我们可以在着色器中使用`mat4`来接收。

```c++
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 transform;
out vec3 ourColor;
out vec2 TexCoord;
void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
};
```

```c++
glm::mat4 trans = glm::mat4(1.0f); // 记得初始化为单位矩阵
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
unsigned int transformUniformLocation = glGetUniformLocation(shader.ID, "transform");
glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, glm::value_ptr(trans));
```

特别需要注意的是，我们优先应用的矩阵变换，应该写在最下面。

---

我们首先查询uniform变量的地址，然后用有`Matrix4fv`后缀的glUniform函数把矩阵数据发送给着色器。第一个参数你现在应该很熟悉了，它是uniform的位置值。

第二个参数告诉OpenGL我们将要发送多少个矩阵，这里是1。

第三个参数询问我们**是否希望对我们的矩阵进行转置**(Transpose)，也就是说交换我们矩阵的行和列。OpenGL开发者通常使用一种内部矩阵布局，叫做列主序(Column-major Ordering)布局。GLM的默认布局就是列主序，所以并不需要转置矩阵，我们填`GL_FALSE`。最后一个参数是真正的矩阵数据，但是GLM并不是把它们的矩阵储存为OpenGL所希望接受的那种，因此我们要先用**GLM的自带的函数value_ptr**来变换这些数据。

---

我们可以将设置矩阵的函数放到我们的Shader类里面

```c++
void setMatrix4(const std::string& name, GLsizei size,GLboolean flag ,GLfloat* value)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), size, flag, value);
}
```

现在我们来写一个持续旋转移动的代码

```c++
glm::mat4 trans = glm::mat4(1.0f); // 注意初始化为单位矩阵
trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
```

然后就可以旋转啦。

## 第六章练习题

6.1 使用应用在箱子上的最后一个变换，尝试将其改变为先旋转，后位移。看看发生了什么，试着想想为什么会发生这样的事情：[参考解答](https://learnopengl.com/code_viewer.php?code=getting-started/transformations-exercise1)

箱子的右下角会移动到中心，也就是位移(-0.5f, 0.5f, 0.0f)，然后以右下角为中心进行九十度旋转

![image-20241205155044875](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205155044875.png)![image-20241205155047056](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205155047056.png)

6.2 尝试再次调用glDrawElements画出第二个箱子，**只**使用变换将其摆放在不同的位置。让这个箱子被摆放在窗口的左上角，并且会不断的缩放（而不是旋转）。（`sin`函数在这里会很有用，不过注意使用`sin`函数时应用负值会导致物体被翻转）：

主要还是涉及到顺序的问题。

如果你采用先平移再缩放的话，那么就会出现6.1中的绕着中心进行缩放的情况。

```c++
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0));
    shader.setMatrix4("transform", 1, GL_FALSE, glm::value_ptr(transform));
```



![image-20241205160532978](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205160532978.png)

如果你采用先缩放再平移的话，那么就会出现绕着物体中心进行缩放然后平移的效果。

```c++
glm::mat4 transform = glm::mat4(1.0f); // reset it to identity matrix
transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
float scaleAmount = static_cast<float>(sin(glfwGetTime()));
transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
shader.setMatrix4("transform", 1, GL_FALSE, glm::value_ptr(transform));
```

![image-20241205160544444](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205160544444.png)

# 7.坐标系统

OpenGL希望在每次顶点着色器运行之后，我们可见的所有顶点都会化为<font color='87CEFA'>**标准化设备坐标**</font>，也就是每个顶点的x，y，z坐标都应该在-1.0到1.0之间。

我们通常会自己设定一个坐标的范围，然后再在顶点着色器中将这些坐标变换为标准化设备坐标，然后将这些<font color='87CEFA'>**标准化设备坐标传入光栅器**</font>，让其变换为屏幕上的二维坐标或者像素。

将坐标变换为标准化设备坐标，接着再转化为屏幕坐标的过程通常是分步进行的。

- <font color='A2CD5A'>**局部空间**</font>(Local Space，或者称为<font color='A2CD5A'>**物体空间(**</font>Object Space))
- <font color='A2CD5A'>**世界空间**</font>(World Space)
- <font color='A2CD5A'>**观察空间**</font>(View Space，或者称为<font color='A2CD5A'>**视觉空间**</font>(Eye Space))
- <font color='A2CD5A'>**裁剪空间**</font>(Clip Space)
- <font color='A2CD5A'>**屏幕空间**</font>(Screen Space)

这就是一个顶点在最终被转化为片段之前需要经历的所有不同状态。

## 概述

为了将坐标从一个坐标系转换到另一个坐标系中，我们需要用到几个变换矩阵。

最重要的几个分别是<font color='A2CD5A'>**模型**</font>(Model)、<font color='A2CD5A'>**观察(**</font>View)、<font color='A2CD5A'>**投影**</font>(Projection)三个矩阵。

我们的顶点坐标起始于<font color='A2CD5A'>**局部空间**</font>(Local Space)，在这里它称为<font color='A2CD5A'>**局部坐标**</font>(Local Coordinate)，它在之后会变为<font color='A2CD5A'>**世界坐标**</font>(World Coordinate)，<font color='A2CD5A'>**观察坐标**</font>(View Coordinate)，<font color='A2CD5A'>**裁剪坐标**</font>(Clip Coordinate)，并最后以<font color='A2CD5A'>**屏幕坐标**</font>(Screen Coordinate)的形式结束。下面的这张图展示了整个流程以及各个变换过程做了什么：

![image-20241205171407490](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205171407490.png)

1. 局部坐标是<font color='87CEFA'>**对象相对于局部原点的坐标**</font>，也是物体起始的坐标。
2. 下一步是将局部坐标变换为世界空间坐标，世界空间坐标是处于一个更大的空间范围的。这些坐标相对于世界的全局原点，它们<font color='87CEFA'>**会和其它物体一起相对于世界的原点进行摆放**</font>。
3. 接下来我们将世界坐标变换为观察空间坐标，使得每个坐标<font color='87CEFA'>**都是从摄像机或者说观察者的角度进行观察**</font>的。
4. 坐标到达观察空间之后，我们需要将其<font color='87CEFA'>**投影到裁剪坐标。裁剪坐标会被处理至-1.0到1.0的范围内**</font>，并判断哪些顶点将会出现在屏幕上。
5. 最后，我们将裁剪坐标变换为屏幕坐标，我们将使用一个叫做<font color='A2CD5A'>**视口变换**</font>的过程。视口变换将位于<font color='CD96CD'>**-1.0**</font>到<font color='CD96CD'>**1.0**</font>范围的坐标变换到由<font color='CD96CD'>**glViewport函数**</font>所定义的坐标范围内。最后变换出来的坐标将会送到光栅器，将其转化为片段。

## 局部空间

局部空间是指物体所在的坐标空间，即<font color='87CEFA'>**对象最开始所在的地方**</font>。

举个例子，你所有的物体最初的原点可能都是<font color='CD96CD'>**(0,0,0)**</font>，但是如果把模型全部放在世界空间中，又可能并不是全在<font color='CD96CD'>**(0,0,0)**</font>。

## 世界空间

我们想为每一个物体定义一个位置，从而能在更大的世界当中放置它们。世界空间中的坐标正如其名：是指顶点相对于（游戏）世界的坐标。如果你希望将物体分散在世界上摆放（特别是非常真实的那样），这就是你希望物体变换到的空间。

物体的坐标将会从<font color='87CEFA'>**局部变换到世界空间**</font>；该变换是由<font color='A2CD5A'>**模型矩阵**</font>(Model Matrix)实现的。

模型矩阵是一种变换矩阵，通过对物体进行位移、缩放、旋转来将它置于它本来应该在的位置或者朝向。

## 观察空间

观察空间通常被称之为<font color='A2CD5A'>**摄像机（摄像机空间，视觉空间）**</font>。

观察空间是<font color='87CEFA'>**将世界空间坐标转化为用户视野前方的坐标而产生的结果**</font>。

而这通常是由一系列的位移和旋转的组合来完成，平移/旋转场景从而使得特定的对象被变换到摄像机的前方。这些组合在一起的变换通常存储在一个<font color='A2CD5A'>**观察矩阵**</font>(View Matrix)里，<font color='87CEFA'>**被用来将世界坐标变换到观察空间**</font>。

## 裁剪空间

在一个顶点着色器运行的最后，OpenGL期望所有的坐标都能落在一个特定的范围内，且任何在这个范围之外的点都应该被<font color='A2CD5A'>**裁剪掉**</font>(Clipped)。被裁剪掉的坐标就会被忽略。

将所有可见的坐标都指定在-1.0到1.0的范围内不是很直观，我们会指定自己的坐标集(Coordinate Set)并将它变换回标准化设备坐标系，就像OpenGL期望的那样。

为了将顶点坐标从观察变换到裁剪空间，我们需要定义一个<font color='A2CD5A'>**投影矩阵**</font>(Projection Matrix)，它指定了一个范围的坐标，比如在每个维度上的-1000到1000。投影矩阵接着会将在这个指定的范围内的坐标变换为标准化设备坐标的范围(-1.0, 1.0)。所有在范围外的坐标不会被映射到在-1.0到1.0的范围之间，所以会被裁剪掉。

>如果只是图元例如三角形的一部分超出了<font color='A2CD5A'>**裁剪体积**</font>的话，那么OpenGL会重新构建这个三角形为一个或者多个三角形，让其能够适合这个裁剪范围。

由投影矩阵创建的观察箱（Viewing Box)被称为<font color='A2CD5A'>**平截头体**</font>(Frustum)，每个出现在平截头体范围内的坐标都会最终出现在用户的屏幕上。将特定范围内的坐标转化到标准化设备坐标系的过程（而且它很容易被映射到2D观察空间坐标）被称之为<font color='A2CD5A'>**投影**</font>(Projection)，因为使用投影矩阵能将3D坐标投影(Project)到很容易映射到2D的标准化设备坐标系中。

一旦所有顶点被变换到裁剪空间，最终的操作——<font color='A2CD5A'>**透视除法**</font>(Perspective Division)将会执行，在这个过程中我们将位置向量的x，y，z分量分别除以向量的<font color='87CEFA'>**齐次w分量**</font>；透视除法是将4D裁剪空间坐标变换为3D标准化设备坐标的过程。这一步会在<font color='87CEFA'>**每一个顶点着色器运行的最后被自动执行**</font>。在这一阶段之后，最终的坐标将会被映射到屏幕空间中（使用<font color='CD96CD'>**glViewport**</font>中的设定），并被变换成片段。

将观察坐标变换为裁剪坐标的投影矩阵可以为两种不同的形式，每种形式都定义了不同的平截头体。我们可以选择创建一个<font color='A2CD5A'>**正射**</font>投影矩阵(Orthographic Projection Matrix)或一个<font color='A2CD5A'>**透视**</font>投影矩阵(Perspective Projection Matrix)。

## 正射投影

正射投影矩阵定义了一个类似立方体的平截头箱，定义了一个裁剪空间，在空间之外的顶点都会被裁剪掉，使用正射投影矩阵变换至裁剪空间之后处于这个平截头内的所有坐标都不会被裁剪掉，可以视为一个容器。

![image-20241205175815486](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205175815486.png)

上面的平截头体定义了可见的坐标，它由宽、高、<font color='A2CD5A'>**近(Near)**</font>平面和<font color='A2CD5A'>**远(Far)**</font>平面所指定。<font color='87CEFA'>**任何出现在近平面之前或远平面之后的坐标都会被裁剪掉**</font>。正射平截头体直接将平截头体内部的所有坐标映射为标准化设备坐标，因为每个向量的w分量都没有进行改变；如果w分量等于1.0，透视除法则不会改变这个坐标。

要创建一个正射投影矩阵，我们可以使用GLM的内置函数`glm::ortho`：

```c++
glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
```

**左（Left）和右（Right）**：这两个参数指定了平截头体在水平坐标轴上的范围。在这个例子中，`0.0f` 和 `800.0f` 表示从左到右的范围是 0 到 800。也就是说，<font color='87CEFA'>**视口的宽度为 800 个单位。**</font>

**底部（Bottom）和顶部（Top）**：这两个参数指定了平截头体在垂直坐标轴上的范围。`0.0f` 和 `600.0f` 表示从底到顶的范围是 0 到 600，<font color='87CEFA'>**视口的高度为 600 个单位。**</font>

**近平面（Near）和远平面（Far）**：这两个参数分别定义了近平面和远平面的位置。在这个例子中，`0.1f` 和 `100.0f` 指定了<font color='87CEFA'>**近平面和远平面分别位于 0.1 和 100 单位的深度**</font>，<font color='87CEFA'>**所有位于这个深度之外的物体将被裁剪掉。**</font>

正射投影矩阵直接将坐标映射到2D平面中，即你的屏幕，但<font color='87CEFA'>**实际上一个直接的投影矩阵会产生不真实的结果**</font>，因为这个投影没有将<font color='A2CD5A'>**透视**</font>(Perspective)考虑进去。所以我们需要<font color='A2CD5A'>**透视投影矩阵**</font>来解决这个问题。

## 透射投影

如果你曾经体验过**实际生活**给你带来的景象，你就会注意到离你越远的东西看起来更小。这个效果称之为<font color='A2CD5A'>**透视**</font>(Perspective)。

![image-20241205181740007](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205181740007.png)

投影矩阵将给定的平截头体范围映射到裁剪空间，除此之外还修改了每个顶点坐标的<font color='87CEFA'>**w值**</font>，从而使得离<font color='87CEFA'>**观察者越远的顶点坐标w分量越大**</font>，被变换到裁剪空间的坐标都会在-w到w的范围之间（任何大于这个范围的坐标都会被裁剪掉）。OpenGL要求所有可见的坐标都落在-1.0到1.0范围内，作为顶点着色器最后的输出，因此，一旦坐标在裁剪空间内之后，透视除法就会被应用到裁剪空间坐标上：

![image-20241205181835224](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205181835224.png)

<font color='87CEFA'>**顶点坐标的每个分量都会除以它的w分量，距离观察者越远顶点坐标就会越小。**</font>这是w分量重要的另一个原因，它能够帮助我们进行透视投影。最后的结果坐标就是处于标准化设备空间中的。

GLM中可以通过下列方式创建一个透视投影矩阵：

```c++
glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
```

它的第一个参数定义了<font color='CD96CD'>**fov**</font>的值，它表示的是<font color='A2CD5A'>**视野**</font>(Field of View)，并且设置了观察空间的大小。如果想要一个真实的观察效果，它的值通常设置为45.0f。

第二个参数设置了<font color='CD96CD'>**宽高比**</font>，由<font color='CD96CD'>**视口的宽除以高**</font>所得。

第三和第四个参数设置了平截头体的<font color='CD96CD'>**近和远平面**</font>。我们通常设置近距离为0.1f，而远距离设为100.0f。所有在近平面和远平面内且处于平截头体内的顶点都会被渲染。

`glm::perspective`所做的其实就是创建了一个定义了可视空间的大**平截头体**，任何在这个平截头体以外的东西最后都不会出现在裁剪空间体积内，并且将会受到裁剪。一个透视平截头体可以被看作一个不均匀形状的箱子，在这个箱子内部的每个坐标都会被映射到裁剪空间上的一个点。

![image-20241205182311136](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205182311136.png)

## 组合变换矩阵

上述的每一个步骤我们都会有一个对应的变换矩阵，因此一个顶点坐标会通过

![image-20241205182818955](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205182818955.png)

注意矩阵运算的顺序是相反的（记住我们需要从右往左阅读矩阵的乘法）。最后的顶点应该被赋值到顶点着色器中的<font color='CD96CD'>**gl_Position**</font>，OpenGL将会自动进行透视除法和裁剪。

**然后呢？**

顶点着色器的输出要求所有的顶点都在裁剪空间内，这正是我们刚才使用变换矩阵所做的。OpenGL然后对**裁剪坐标**执行**透视除法**从而将它们变换到**标准化设备坐标**。OpenGL会使用<font color='CD96CD'>**glViewPort**</font>内部的参数来将标准化设备坐标映射到**屏幕坐标**，每个坐标都关联了一个屏幕上的点（在我们的例子中是一个800x600的屏幕）。这个过程称为视口变换。

## 开写代码

### 模型矩阵

首先构建模型矩阵，将物体转换到全局的世界空间。

我们首先需要变换我们的平面，让其不要和我们的屏幕平行，而是绕<font color='CD96CD'>**x**</font>轴旋转<font color='CD96CD'>**55°**</font>。

```c++
glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, glm::radians(55.0f), vec3(1.0f, 0.0f, 0.0f));
```

### 观察矩阵

我们需要在场景里面稍微往后移动，让物体变成可见的样子。

```c++
glm::mat4 view;
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
```

以相反于摄像机移动的方向移动整个场景。因为我们想要往后移动，并且OpenGL是一个右手坐标系(Right-handed System)，所以我们需要沿着z轴的正方向移动。我们会通过将场景沿着z轴负方向平移来实现。它会给我们一种我们在往后移动的感觉。

<font color='87CEFA'>**就可以简单理解为，在右手坐标系中，正z轴是指向观察者的。而负z轴是指向观察者的方向，当你将场景沿z轴的负方向平移时，实际是将物体向观察者移动，或者说是让物体“变得可见”。**</font>

**右手坐标系(Right-handed System)**

按照惯例，OpenGL是一个右手坐标系。简单来说，就是正x轴在你的右手边，正y轴朝上，而正z轴是朝向后方的。想象你的屏幕处于三个轴的中心，则正z轴穿过你的屏幕朝向你。坐标系画起来如下：

![image-20241205183951156](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205183951156.png)

为了理解为什么被称为右手坐标系，按如下的步骤做：

- 沿着正y轴方向伸出你的右臂，手指着上方。
- 大拇指指向右方。
- 食指指向上方。
- 中指向下弯曲90度。

如果你的动作正确，那么你的大拇指指向正x轴方向，食指指向正y轴方向，中指指向正z轴方向。如果你用左臂来做这些动作，你会发现z轴的方向是相反的。这个叫做左手坐标系，它被DirectX广泛地使用。注意在标准化设备坐标系中OpenGL实际上使用的是左手坐标系（投影矩阵交换了左右手）。

### 投影矩阵

```c++
glm::mat4 projection = glm::mat4(1.0f);
projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
```

既然我们创建了变换矩阵之后，我们就需要在顶点着色器之中声明一个uniform变换然后将它乘以对应的顶点坐标。

```c++
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
};
```

```c++
// 设置变换矩阵
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

// 创建矩阵
model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
int modelUniformLocation = glGetUniformLocation(shader.ID, "model");
int viewUniformLocation = glGetUniformLocation(shader.ID, "view");
int projectionUniformLocation = glGetUniformLocation(shader.ID, "projection");

glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));
glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
```

或者采用下面的代码都是可以的

```c++
shader.setMatrix4("model", 1, GL_FALSE, glm::value_ptr(model));
shader.setMatrix4("view", 1, GL_FALSE, glm::value_ptr(view));
shader.setMatrix4("projection", 1, GL_FALSE, glm::value_ptr(projection));
```

![image-20241205191432586](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205191432586.png)

