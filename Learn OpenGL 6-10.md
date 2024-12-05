# 6.变换

我们可以尝试在每一帧去改变物体的顶点并且重新配置缓冲区来使其移动，但是这太繁琐了，而且会消耗非常多的处理时间。

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
