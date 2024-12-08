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

我们现在可以生成六个平面来作为一个立方体：

```c++
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
```

注意，我们这里并没有<font color='CD96CD'>**color**</font>这个参数，因此，我们在传递顶点数据的时候记得修改以下，还有<font color='CD96CD'>**.vs**</font><font color='CD96CD'>**顶点着色器**</font>里面<font color='CD96CD'>**location**</font>也需要修改。

```c++
// 设置位置属性
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// 设置纹理坐标属性
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```

```c++
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

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

然后我们调用<font color='CD96CD'>**glDrawArrays**</font>就可以了。

```c++
glDrawArrays(GL_TRIANGLES, 0, 36);
```

![image-20241205195220909](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205195220909.png)

虽然效果是有点奇怪，但是是正确的。

>立方体的某些本应被遮挡住的面被绘制在了这个立方体其他面之上。之所以这样是因为<font color='87CEFA'>**OpenGL是一个三角形一个三角形地来绘制你的立方体的**</font>，<font color='87CEFA'>**所以即便之前那里有东西它也会覆盖之前的像素。因为这个原因，有些三角形会被绘制在其它三角形上面**</font>，虽然它们本不应该是被覆盖的。

## Z缓冲

OpenGL存储深度信息在一个叫做<font color='A2CD5A'>**Z缓冲**</font>的缓冲中，允许OpenGL决定何时覆盖一个像素而何时不覆盖这个像素。

OpenGL存储它的所有深度信息于一个Z缓冲(Z-buffer)中，也被称为深度缓冲(Depth Buffer)。GLFW会自动为你生成这样一个缓冲（就像它也有一个颜色缓冲来存储输出图像的颜色）。深度值存储在每个片段里面（作为片段的**z**值），<font color='87CEFA'>**当片段想要输出它的颜色时，OpenGL会将它的深度值和z缓冲进行比较，如果当前的片段在其它片段之后，它将会被丢弃，否则将会覆盖。**</font>这个过程称为深度测试(Depth Testing)，它是由OpenGL自动完成的。

我们可以通过<font color='CD96CD'>**glEnable**</font>函数来开启深度测试，<font color='CD96CD'>**glEnable**</font>和<font color='CD96CD'>**glDisable**</font>函数允许我们启用或禁用某个OpenGL功能。这个功能会一直保持启用/禁用状态

```c++
glEnable(GL_DEPTH_TEST);
```

但是尽管我们使用了深度测试，我们也需要在每次渲染迭代之前清除深度缓冲（否则前一帧的深度信息将会保存在缓冲当中），通过glClear来清除。

```c++
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)；
```

<font color='FFD00'>**Congratulations！**</font>

![image-20241205200032348](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205200032348.png)

```c++
glm::vec3 cubePositions[] =
{
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
for (glm::vec3 cubePosition : cubePositions)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePosition);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shader.setMatrix4("model", 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
```

![image-20241205201036980](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241205201036980.png)

## 第七章练习题

- 对GLM的`projection`函数中的`FoV`和`aspect-ratio`参数进行实验。看能否搞懂它们是如何影响透视平截头体的。

  1. **FoV（视场角）**：
     - `FoV`决定了摄像机视野的宽度。较大的`FoV`值会让视野变得更宽广，从而使物体看起来更小、更远；而较小的`FoV`值则会让视野变窄，物体看起来更大、更近。
     - 通常，`FoV`是以度为单位指定的，影响近裁剪面和远裁剪面的距离，并且改变透视效果，使其变得更夸张（广角效果）或更压缩（长焦效果）。
  2. **Aspect Ratio（宽高比）**：
     - `aspect-ratio`定义了视口（或屏幕）的宽高比，确保透视平截头体不变形。常见的宽高比比如16:9表示宽度是高度的16/9倍。
     - 如果`aspect-ratio`设置不当，图像可能会出现拉伸或压缩的现象。

  要进行实验，你可以通过调整`FoV`和`aspect-ratio`的值来观察透视平截头体的变化：

  - **改变`FoV`**：观察摄像机视野如何变宽或变窄，物体的远近效果如何变化。
  - **改变`aspect-ratio`**：观察不同宽高比下，物体在屏幕上如何呈现，是否出现拉伸或压缩。

  我们可以通过修改代码来实时观看变化：

  ```c++
  void processInput(GLFWwindow* window)
  {
  	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  	{
  		glfwSetWindowShouldClose(window, true);
  	}
  	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
  	{
  		mixValue = std::min(1.0f, mixValue + 0.01f);
  		fov = std::min(180.0f, fov + 1.0f);
  	}
  
  	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
  	{
  		mixValue = std::max(0.0f, mixValue - 0.01f);
  		fov = std::max(0.0f, fov - 1.0f);
  	}
  }
  ```

  其实你能看到增大fov的时候，整个视角都会被拉远，减小fov的时候视角会拉近，但是物体并不会被压缩变形。

- 将观察矩阵在各个方向上进行位移，来看看场景是如何改变的。注意把观察矩阵当成摄像机对象。

  你可以理解为如果观察矩阵向右上角移动的话，那么摄像机其实是向左下角移动的，就是摄像机的移动方向和观察矩阵是相反的。

- 使用模型矩阵只让是3倍数的箱子旋转（以及第1个箱子），而让剩下的箱子保持静止。[参考解答](https://learnopengl.com/code_viewer.php?code=getting-started/coordinate_systems-exercise3)。

  ```c++
  if(i % 3 == 0)
      model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
  else
      model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
  ```

# 8.摄像机

OpenGL中本身并没有<font color='A2CD5A'>**摄像机**</font>的概念，我们可以通过把场景中的所有物体往相反方向移动的方式来模拟出摄像机。

本节目标：

①在OpenGL中配置一个摄像机，能够在3D场景中自由移动。

②设置键盘和鼠标输入，最终完成一个自定义的摄像机类。

## 摄像机/观察空间

摄像机的视角作为场景原点时场景中所有的顶点坐标

我们讨论<font color='A2CD5A'>**摄像机/观察空间**</font>(Camera/View Space)的时候，是在<font color='87CEFA'>**讨论以摄像机的视角作为场景原点时场景中所有的顶点坐标**</font>

观察矩阵的作用就是将所有的世界坐标变换为相对于摄像机位置与方向的观察坐标，定义一个摄像机，需要<font color='87CEFA'>**创建一个三个单位轴相互垂直的、以摄像机的位置为原点的坐标系**</font>。

![image-20241208134752881](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208134752881.png)

### 摄像机位置

摄像机位置简单来说就是<font color='87CEFA'>**世界空间中一个指向摄像机位置的向量**</font>。我们把摄像机位置设置为上一节中的那个相同的位置：

```c++
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
```

这里是`+3.0f`而不是`-3.0f`，不要忘记<font color='87CEFA'>**正z轴是从屏幕指向你的**</font>，如果我们希望摄像机向后移动，我们就沿着z轴的正方向移动。

### 摄像机指向方向

我们知道摄像机<font color='87CEFA'>**指向z轴负方向**</font>，但我们希望方向向量(Direction Vector)指向摄像机的z轴正方向。如果我们交换相减的顺序，我们就会获得一个指向摄像机正z轴方向的向量：

```c++
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
```

<font color='A2CD5A'>**方向向量**</font>(Direction Vector)并不是最好的名字，因为它<font color='87CEFA'>**实际上指向从它到目标向量的相反方向**</font>

### 右轴

我们需要的另一个向量是一个<font color='A2CD5A'>**右向量**</font>(Right Vector)，它<font color='87CEFA'>**代表摄像机空间的x轴的正方向**</font>。为获取右向量我们需要先定义一个<font color='A2CD5A'>**上向量**</font>(Up Vector)。<font color='87CEFA'>**接下来把上向量和第二步得到的方向向量进行叉乘。两个向量叉乘的结果会同时垂直于两向量**</font>，因此我们会得到指向x轴正方向的那个向量（<font color='FFD00'>**如果我们交换两个向量叉乘的顺序就会得到相反的指向x轴负方向的向量**</font>）

```c++
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
```

### 上轴

我们把<font color='A2CD5A'>**右向量**</font>和<font color='A2CD5A'>**方向向量**</font>进行叉乘：

```c++
glm::vec3 cameraUp = glm::vec3(glm::cross(cameraDirection, cameraRight));
```

---

现在使用这些摄像机向量我们就可以创建一个LookAt矩阵，用于创建摄像机。

## Look At

可以通过三个摄像机轴向量（加上平移向量）来创建一个矩阵，这样可以用这个矩阵乘以任何向量来将其变换到那个坐标空间，这就是<font color='A2CD5A'>**LookAt矩阵**</font>。

![image-20241208140148085](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208140148085.png)

<font color='FFD00'>**位置向量是相反的**</font>，因为我们<font color='87CEFA'>**最终希望把世界平移到与我们自身移动的相反方向**</font>。把这个<font color='A2CD5A'>**LookAt**</font>矩阵作为观察矩阵可以很高效地把所有世界坐标变换到刚刚定义的观察空间。<font color='A2CD5A'>**LookAt**</font>矩阵就像它的名字表达的那样：它会创建一个看着(Look at)给定目标的观察矩阵。

在GLM中我们可以通过给定一个摄像机位置，一个目标位置，一个表示世界空间中的上向量的向量，然后GLM就会创建一个LookAt矩阵了，我们可以将其作为我们的观察矩阵。

```c++
glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), // 摄像机位置
                  glm::vec3(0.0f, 0.0f, 0.0f),  // 目标位置
                  glm::vec3(0.0f, 1.0f, 0.0f)); // 上向量
```

![image-20241208140724184](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208140724184.png)

得到的结果其实和之前是一样的。

我们可以让摄像机进行旋转，只要保证目标位置不变即可。

```c++
double radius = 10.0f;
double cameraX = sin(glfwGetTime()) * radius;
double cameraZ = cos(glfwGetTime()) * radius;
glm::mat4 view = glm::mat4(1.0f);
view = glm::lookAt(glm::vec3(cameraX, 0.0f ,cameraZ),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));
```

![image-20241208141028468](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208141028468.png)

我们应该在XOZ平面中旋转，所以改变X轴和Z轴向量即可。

我们也可以进行自由移动，为摄像机定义一些向量变量

```c++
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
```

依然在`processInput`里面来处理：

```c++
	double cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos.x += cameraSpeed * cameraFront.x;
		cameraPos.y += cameraSpeed * cameraFront.y;
		cameraPos.z += cameraSpeed * cameraFront.z;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos.x -= cameraSpeed * cameraFront.x;
		cameraPos.y -= cameraSpeed * cameraFront.y;
		cameraPos.z -= cameraSpeed * cameraFront.z;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos.x += cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront)).x;
		cameraPos.y += cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront)).y;
		cameraPos.z += cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront)).z;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos.x -= cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront)).x;
		cameraPos.y -= cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront)).y;
		cameraPos.z -= cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront)).z;
	}
```

注意，我们对**右向量**进行了标准化。<font color='FFD00'>**如果我们没对这个向量进行标准化，最后的叉乘结果会根据cameraFront变量返回大小不同的向量**</font>。如果我们不对向量进行标准化，我们就得根据摄像机的朝向不同加速或减速移动了，但如果进行了标准化移动就是匀速的。

## 移动速度

目前我们的移动速度是一个常量，按道理来说是没有问题的，但是根据处理器的不同，不同的电脑每秒绘制的帧数可能并不同，因此我们必须确保在所有硬件上的移动速度都是一样的。

图形程序和游戏通常会跟踪一个<font color='A2CD5A'>**时间差**</font>(deltaTime)，它存储了渲染上一帧需要用的时间，我们将所有的速度都去乘以deltaTime值，结果就是如果我们的deltaTime值变得很大，就意味着上一帧渲染花费了更多的时间，所以这一帧的速度就需要变得更高去平衡渲染所花去的时间

```c++
// 全局变量
float lastFrame = 0.0f; // 上一帧的时间
float deltaTime = 0.0f; // 当前帧与上一帧的时间差

double cameraSpeed = 2.5f * deltaTime;
if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
while (!glfwWindowShouldClose(window))
{
    //...
    float currentFrame = static_cast<float>(glfwGetTime()); // 记录当前的时间
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //...
}

```

## 视角移动

为了能够改变视角，我们需要根据<font color='87CEFA'>**鼠标的输入**</font>来改变<font color='CD96CD'>**cameraFront**</font>向量

### 欧拉角

是可以表示3D空间中任何旋转的3个值。<font color='A2CD5A'>**俯仰角**</font>(Pitch)、<font color='A2CD5A'>**偏航角**</font>(Yaw)和<font color='A2CD5A'>**滚转角**</font>(Roll)，下面的图片展示了它们的含义：

<font color='87CEFA'>**俯仰角是描述我们如何往上或往下看的角**</font>，<font color='87CEFA'>**偏航角表示我们往左和往右看的程度**</font>。<font color='87CEFA'>**滚转角代表我们如何翻滚摄像机**</font>。每个欧拉角都有一个值来表示，把三个角结合起来我们就能够计算3D空间中任何的旋转向量了。

对于常见的摄像机系统来说，我们只关心俯仰角和偏航角。

给定一个俯仰角和偏航角，我们可以将其转换为一个代表新的方向向量的3D向量。

![image-20241208145812096](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208145812096.png)

如果我们把斜边边长定义为1，我们就能知道邻边的长度是`cos x/h=cos x/1=cos xcos⁡ x/h=cos⁡ x/1=cos⁡ x`，它的对边是`sin y/h=sin y/1=sin ysin⁡ y/h=sin⁡ y/1=sin⁡ y`。这样我们获得了能够得到x和y方向长度的通用公式，它们取决于所给的角度。我们使用它来计算方向向量的分量：

![image-20241208145935424](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208145935424.png)

这个三角形看起来和前面的三角形很像，所以如果我们想象自己在<font color='CD96CD'>**xz**</font>平面上，看向<font color='CD96CD'>**y**</font>轴，我们可以基于第一个三角形计算来计算它的长度/y方向的强度(Strength)（我们往上或往下看多少）。从图中我们可以看到对于一个给定俯仰角的y值等于sin θ：

```c++
// 注意我们这里假设了斜边长是1，所以sin y = y / 1;
direction.y = sin(glm::radians(pitch)); // 注意我们先把角度转为弧度
```

这里我们只更新了y的值，仔细观察x和z分量也被影响了，从三角形中我们可以看到其实就是cos值。

```c++
direction.x = cos(glm::radians(pitch));
direction.z = cos(glm::radians(pitch));
```

其实我们可以看到，如果是俯仰角的话，我们其实可以看作是在<font color='CD96CD'>**XOY**</font>平面内找

如果是偏航角的话，我们可以看作是在<font color='CD96CD'>**XOZ**</font>平面内找

![image-20241208150941643](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241208150941643.png)

```c++
direction.z = sin(glm::radians(yaw));
direction.x = cos(glm::radians(yaw));
```

没有y方向的分量，如果我们和之前的pitch相关的分量结合起来的话。

```c++
direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
direction.y = sin(glm::radians(pitch));
direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
```

这样的话我们就可以把俯仰角和偏航角转化为用来自由旋转视角的摄像机的3维方向向量了。

接下来要做的事，如何获取**俯仰角和偏航角**？

## 鼠标输入

水平的移动影响偏航角，竖直的移动影响俯仰角，原理就是，<font color='87CEFA'>**储存上一帧鼠标的位置，在当前帧中我们当前计算鼠标位置与上一帧的位置差多少**</font>。

首先我们应该隐藏光标并捕捉它，捕捉光标的表示是，如果焦点在你的程序上，那么光标应该停留在窗口中。

```c++
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
```

调用这个函数之后，无论我们怎么去移动鼠标，光标都不会显示了，也不会离开窗口。对于FPS摄像机系统来说非常完美。

为了计算俯仰角和偏航角，我们需要让GLFW监听鼠标移动事件。我们通过一个回调函数来完成。

```c++
void mouse_callback(GLFWWindow* window, doble xPos, double yPos);
```

这里的`xpos`和`ypos`代表当前鼠标的位置。当我们用GLFW注册了回调函数之后，鼠标一移动`mouse_callback`函数就会被调用：

```c++
glfwSetCursorPosCallback(window, mouse_callback);
```

在处理FPS风格摄像机的鼠标输入的时候，我们在最终获取方向向量之前做下面几步：

+ 计算鼠标距上一帧的偏移量。
+ 把偏移量添加到摄像机的俯仰角和偏航角中。
+ 对偏航角和俯仰角进行最大和最小值的限制。
+ 计算方向向量。

计算鼠标距上一帧的偏移量：

```c++
float lastX = SCREENWIDTH / 2;
float lastY = SCREENHEIGHT / 2;
```

在鼠标的回调函数这种，我们计算当前帧和上一帧鼠标位置的偏移量:

```c++
float xOffset = xPos - lastX;
float yOffset = lastY - yPos;
lasyX = xPos;
lastY = yPos;

float sensitivity = 0.05f;
xOffset *= sensitivity;
yOffset *= sensitivity;
```

然后我们将偏移量加到全局变量`pitch`和`yaw`之上

```c++
pitch += yOffset;
yaw += xOffset;
```

然后我们为摄像机添加一个限制，俯仰角的绝对值不能超过89°，否则会发生反转

```c++
if(pitch > 89.0f) pitch = 89.0f;
if(pitch < -89.0f) pitch = -89.0f;
```

偏航角就不用设置限制，然后我们可以通过俯仰角和偏航角来计算得到真正的方向向量。

```c++
glm::vec3 front;
front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
front.y = sin(glm::radians(pitch));
front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
cameraFront = glm::normalize(front);
```

第一次在获取焦点的时候摄像机会跳一下，主要就是因为鼠标移动进窗口的那一瞬间，鼠标回调函数就会被调用，这个时候的xPos和yPos就会等于鼠标刚刚进入屏幕的位置，然后产生一个比较大的偏移量。

## 缩放

上一节课的fov这节课就能够使用了。我们通过鼠标滚轮来实现。

```c++
void scroll_callback(GLFWwindow* widnow, double xOffset, double yOffset)
{
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yOffset;
    if(fov <= 1.0f) fov = 1.0f;
    if(fov >= 45.0f) fov = 45.0f;
}
```

然后不要忘记注册

```c++
glfwSetScrollCallback(window, scroll_callback);
```

使用：

```c++
projection = glm::perspective(glm::radians(fov), SCREENWIDTH / SCREENHEIGHT, 0.1f, 100.0f);
```

## 摄像机类（***）

```c++
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement 
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera 
{
public:
    // Camera Attributes
    // 用于定义LookAt矩阵
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;

    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() 
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = deltaTime * MovementSpeed;
        if (direction == FORWARD)
        {
            Position += Front * velocity;
        }
        if (direction == BACKWARD)
        {
            Position -= Front * velocity;
        }
        if (direction == RIGHT)
        {
            Position += Right * velocity;
        }
        if (direction == LEFT)
        {
            Position -= Right * velocity;
        }
    }

    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
    {
        xOffset *= MouseSensivity;
        yOffset *= MouseSensivity;

        Pitch += yOffset;
        Yaw += xOffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yOffset)
    {
        Zoom -= (float)yOffset;
        if (Zoom < 1.0f) Zoom = 1.0f;
        if (Zoom > 45.0f) Zoom = 45.0f;
    }

private:

    // 用于更新摄像机方向坐标系
    void updateCameraVectors() 
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
        front.y = sin(glm::radians(Pitch));
        front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));

        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif // !CAMERA_H

```

```c++
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../../../headfile/Shader/Shader.h>
#include "../../../headfile/stb_image/stb_image.h"

// GLM(OpenGL Mathmatics)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// c++
#include <iostream>
#include <algorithm>

// file
#include <filesystem>
#include "../../headfile/Camera/Camera.h"

#define SOLUTION_DIR "D:\\repo\\OpenGL\\OpenGL"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* widnow, double xOffset, double yOffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;
float pitch = 0;
float yaw = 0;
bool firstMouse = true;
float fov = 45.0f;

float lastFrame = 0.0f; // 上一帧的时间
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float mixValue = 0.2f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL_ForRiver", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return-1;
	}

	// 窗口位置X，窗口位置Y，窗口宽度，窗口高度
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// 生成 VAO, VBO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 绑定 VAO
	glBindVertexArray(VAO);

	// 绑定 VBO 并传入数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 设置位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 设置纹理坐标属性
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 组合解决方案目录和相对路径
	std::filesystem::path vertexPath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "ShaderSource" / "Chapter_8_Camera" / "Shader_8.vs";
	std::filesystem::path fragmentPath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "ShaderSource" / "Chapter_8_Camera" / "Shader_8.fs";

	// 获取绝对路径
	std::filesystem::path vertexAbsolutePath = std::filesystem::absolute(vertexPath);
	std::filesystem::path fragmentAbsolutePath = std::filesystem::absolute(fragmentPath);

	Shader shader(vertexAbsolutePath.string().c_str(), fragmentAbsolutePath.string().c_str());

	// 生成纹理对象
	std::filesystem::path texturePath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "Figure" / "container.jpg";

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// 重复环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 镜像环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// 边界拉伸
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// 指定边缘颜色
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 0.5f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	// 加载纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.string().c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 加载图像
	std::filesystem::path awesomefacePath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "Figure" / "awesomeface.png";
	data = stbi_load(awesomefacePath.string().c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load image." << std::endl;
	}
	stbi_image_free(data);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	// 设置变换矩阵



	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置函数
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 状态使用函数

		float currentFrame = static_cast<float>(glfwGetTime()); // 记录当前的时间
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		shader.use();
		shader.setFloat("mixValue", mixValue);

		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++)
		{
			glm::vec3 cubePosition = cubePositions[i];
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition);
			if(i % 3 == 0)
				model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			else
				model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
			shader.setMatrix4("model", 1, GL_FALSE, glm::value_ptr(model));
			shader.setMatrix4("view", 1, GL_FALSE, glm::value_ptr(view));
			shader.setMatrix4("projection", 1, GL_FALSE, glm::value_ptr(projection));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;  // 更新鼠标位置
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset, true);
}
void scroll_callback(GLFWwindow* widnow, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(yOffset);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue = std::min(1.0f, mixValue + 0.01f);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue = std::max(0.0f, mixValue - 0.01f);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}
```

## 第八章 练习题

- 看看你是否能够修改摄像机类，使得其能够变成一个真正的FPS摄像机（也就是说不能够随意飞行）；你只能够呆在xz平面上：[参考解答](https://learnopengl.com/code_viewer.php?code=getting-started/camera-exercise1)

  其实也就是将位置限定在y轴。

  ```c++
  Position.y = 0;
  ```

- 试着创建你自己的LookAt函数，其中你需要手动创建一个我们在一开始讨论的观察矩阵。用你的函数实现来替换GLM的LookAt函数，看看它是否还能一样地工作：[参考解答](https://learnopengl.com/code_viewer.php?code=getting-started/camera-exercise2)

  注意点：<font color='FFD00'>**在 OpenGL 中，矩阵是 **列主序**（column-major order）的**</font>，即矩阵的元素按照列而不是行进行存储和操作。GLM 作为 OpenGL 数学库，遵循这一约定。具体到 `glm::mat4` 这样的 4x4 矩阵，它的内存布局是按列主序存储的。

  `mat[0][0]` 是矩阵的第一个列，第一个元素。

  `mat[1][0]` 是矩阵的第二列，第一个元素，依此类推。

  ```c++
  | m00 m10 m20 m30 |
  | m01 m11 m21 m31 |
  | m02 m12 m22 m32 |
  | m03 m13 m23 m33 |
  ```

  ```c++
  glm::mat4 getViewMatrix() 
  {
      glm::mat4 transform = glm::mat4(1.0f);
      transform[3][0] = -Position.x;
      transform[3][1] = -Position.y;
      transform[3][2] = -Position.z;
  
      glm::mat4 rotation = glm::mat4(1.0f);
      rotation[0][0] = Right.x;
      rotation[1][0] = Right.y;
      rotation[2][0] = Right.z;
      rotation[0][1] = Up.x;
      rotation[1][1] = Up.y;
      rotation[2][1] = Up.z;
      rotation[0][2] = -Front.x;
      rotation[1][2] = -Front.y;
      rotation[2][2] = -Front.z;
  
      return rotation * transform;
      //return glm::lookAt(Position, Position + Front, Up);
  }
  ```

  # 复习

  - **OpenGL**： 一个定义了函数布局和输出的图形API的正式规范。
  - **GLAD**： 一个扩展加载库，用来为我们加载并设定所有OpenGL函数指针，从而让我们能够使用所有（现代）OpenGL函数。
  - **视口(Viewport)**： 我们需要渲染的窗口。
  - **图形管线(Graphics Pipeline)**： 一个顶点在呈现为像素之前经过的全部过程。
  - **着色器(Shader)**： 一个运行在显卡上的小型程序。很多阶段的图形管道都可以使用自定义的着色器来代替原有的功能。
  - **标准化设备坐标(Normalized Device Coordinates, NDC)**： 顶点在通过在剪裁坐标系中剪裁与透视除法后最终呈现在的坐标系。所有位置在NDC下-1.0到1.0的顶点将不会被丢弃并且可见。
  - **顶点缓冲对象(Vertex Buffer Object)**： 一个调用显存并存储所有顶点数据供显卡使用的缓冲对象。
  - **顶点数组对象(Vertex Array Object)**： 存储缓冲区和顶点属性状态。
  - **元素缓冲对象(Element Buffer Object，EBO)，也叫索引缓冲对象(Index Buffer Object，IBO)**： 一个存储元素索引供索引化绘制使用的缓冲对象。
  - **Uniform**： 一个特殊类型的GLSL变量。它是全局的（在一个着色器程序中每一个着色器都能够访问uniform变量），并且只需要被设定一次。
  - **纹理(Texture)**： 一种包裹着物体的特殊类型图像，给物体精细的视觉效果。
  - **纹理环绕(Texture Wrapping)**： 定义了一种当纹理顶点超出范围(0, 1)时指定OpenGL如何采样纹理的模式。
  - **纹理过滤(Texture Filtering)**： 定义了一种当有多种纹素选择时指定OpenGL如何采样纹理的模式。这通常在纹理被放大情况下发生。
  - **多级渐远纹理(Mipmaps)**： 被存储的材质的一些缩小版本，根据距观察者的距离会使用材质的合适大小。
  - **stb_image.h**： 图像加载库。
  - **纹理单元(Texture Units)**： 通过绑定纹理到不同纹理单元从而允许多个纹理在同一对象上渲染。
  - **向量(Vector)**： 一个定义了在空间中方向和/或位置的数学实体。
  - **矩阵(Matrix)**： 一个矩形阵列的数学表达式。
  - **GLM**： 一个为OpenGL打造的数学库。
  - **局部空间(Local Space)**： 一个物体的初始空间。所有的坐标都是相对于物体的原点的。
  - **世界空间(World Space)**： 所有的坐标都相对于全局原点。
  - **观察空间(View Space)**： 所有的坐标都是从摄像机的视角观察的。
  - **裁剪空间(Clip Space)**： 所有的坐标都是从摄像机视角观察的，但是该空间应用了投影。这个空间应该是一个顶点坐标最终的空间，作为顶点着色器的输出。OpenGL负责处理剩下的事情（裁剪/透视除法）。
  - **屏幕空间(Screen Space)**： 所有的坐标都由屏幕视角来观察。坐标的范围是从0到屏幕的宽/高。
  - **LookAt矩阵**： 一种特殊类型的观察矩阵，它创建了一个坐标系，其中所有坐标都根据从一个位置正在观察目标的用户旋转或者平移。
  - **欧拉角(Euler Angles)**： 被定义为偏航角(Yaw)，俯仰角(Pitch)，和滚转角(Roll)从而允许我们通过这三个值构造任何3D方向。
