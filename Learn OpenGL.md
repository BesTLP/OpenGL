# Learn OpenGL

# 1. OpenGL

被认为是一个API，包含了一系列**可以操作图形、图像的函数**。

然而，**OpenGL本身并不是一个API**，它仅仅是一个规范(Specification)。

也就是OpenGL并没有函数的具体实现，而只是告诉你每个函数应该如何执行，以及应该输出什么。

开发由显卡生产商来专门开发。

##  核心模式与立即渲染模式

早期的OpenGL使用立即渲染模式，也就是固定渲染管线

> 立即渲染模式容易使用和理解，但是效率太低
>
> 开发者很少有控制OpenGL如何进行计算的自由

OpenGL3.2开始，规范文档开始废弃立即渲染模式，鼓励开发者在OpenGL的**核心模式**下开发。

我们从OpenGL3.3 开始学习，因为所有更高版本的OpenGL都是在3.3的基础之上引入了额外的功能，核心架构都没有改变。、

## 状态机

OpenGL自身是一个**状态机**，我们通过**一系列的变量描述**OpenGL此刻应当如何运行。

OpenGL的状态通常被称为上下文，通常使用如下途径去**更改OpenGL状态**：设置选项，操作缓冲。最后，我们使用当前OpenGL上下文来渲染。

使用OpenGL时，最关键的是了解状态设置函数和状态使用函数。

+ **状态设置函数**(State-changing Function)，这类函数将会改变上下文。

+ **状态使用函数(**State-using Function)，这类函数会根据当前OpenGL的状态执行一些操作。

我们改变**上下文变量**让OpenGL去绘制三角形还是线段。

当我们使用对象的时候，可以将OpenGL上下文看作是一个大的结构体。

> 使用对象的一个好处是，在我们执行一个使用OpenGL状态的操作的时候，只需要绑定含有需要的设置的对象即可。

```c++
// 创建对象
unsigned int objectId = 0;
glGenObject(1, &objectId);
// 绑定对象至上下文
glBindObject(GL_WINDOW_TARGET, objectId);
// 设置当前绑定到 GL_WINDOW_TARGET 的对象的一些选项
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH, 800);
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
// 将上下文对象设回默认
glBindObject(GL_WINDOW_TARGET, 0);
```

ss这一小段代码展现了你以后使用OpenGL时常见的工作流。

我们首先创建一个对象，然后用一个id保存它的引用（实际数据被储存在后台）。

然后我们将对象绑定至上下文的目标位置（例子中窗口对象目标的位置被定义成GL_WINDOW_TARGET）。

接下来我们设置窗口的选项。

最后我们将目标位置的对象id设回0，解绑这个对象。

设置的选项将被保存在objectId所引用的对象中，一旦我们重新绑定这个对象到GL_WINDOW_TARGET位置，这些选项就会重新生效。

# 2. 创建窗口

## GLFW

下载GLFW并配置好对应的Include和Lib目录

```c++
$(SolutionDir)OpenGL\Dependencies\GLFW\include
```

```c++
$(SolutionDir)OpenGL\Dependencies\GLFW\lib-vc2015
```

附加依赖项，如果出现问题的话，到输出窗口查看报错信息，然后去Google一下，看看是少了哪个附加依赖项就好

```c++
glfw3.lib
opengl32.lib
```

然后copy官网的代码

```c++
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```

Run！

![image-20241130110706164](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130110706164.png)

绘制三角形

![image-20241130111209373](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130111209373.png)

```c++
// 绘制三角形
glBegin(GL_TRIANGLES);
glVertex2f(0, 0);
glVertex2f(0.5, 1);
glVertex2f(1, 0);
glEnd();
```

## 使用现代OpenGL(GLEW*可选)

下载GLEW，配置附加包含目录和库依赖

```C++
$(SolutionDir)OpenGL\Dependencies\GLEW\include
```

```C++
$(SolutionDir)OpenGL\Dependencies\GLEW\lib\Release\Win32
```

```C++
glew32s.lib
```

如果你直接调用

```c++
glewInit();
```

的话，会出现问题

```c++
 error LNK2019: 无法解析的外部符号 __imp__glewInit@0，函数 _main 中引用了该符号
```

我们寻找一下glewInit()这个函数的定义

![image-20241130113313843](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130113313843.png)

![image-20241130113324273](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130113324273.png)

进入GLEWAPI之后我们会发现是因为我们使用了静态库，但是却没有定义GLEW_STATIC导致的，所以我们需要定义GLEW_STATIC，否则就会默认走GLEW_BUILD，也就是从dll文件导入，但是实际上我们并没有dll文件 

![image-20241130113450755](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130113450755.png)

我们调用glewInit()的时候需要获取一个OpenGL context，否则就会报错

![image-20241130113940847](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130113940847.png)

## GLAD

OpenGL只是一个规范，大多数函数的位置都无法在编译的时候确定下来，因此需要在运行的时候查询。

开发者需要在运行的时候获取函数地址并将其保存在一个函数指针中供以后使用。

例如Windows

```c++
// 定义函数原型
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// 找到正确的函数并赋值给函数指针
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// 现在函数可以被正常调用了
GLuint buffer;
glGenBuffers(1, &buffer);
```

GLAD可以简化这种方式，以便我们不用对每个可能使用的函数都重复这个过程。

下载GLAD([glad.dav1d.de](https://glad.dav1d.de/))

![image-20241202170741704](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202170741704.png)

然后添加附加包含目录和库目录，很简单的。

## 指定版本号和核心模式

```c++
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit(); // 初始化glfw
    // 主版本号和次版本号都设置为3.3，说明咱们要用的是3.3的OpenGL.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 明确告诉GLFW我们使用的是核心模式(Core_Profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}
```

我们在main函数中调用glfwInit函数来初始化GLFW。

然后我们可以使用glfwWindowHint函数来配置GLFW。

glfwWindowHint函数的第一个参数代表选项的名称，我们可以从很多以`GLFW_`开头的枚举值中选择；

第二个参数接受一个整型，用来设置这个选项的值。

## 创建窗口对象

```c++
GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL_ForRiver", NULL, NULL);
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window);
```

创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。

## GLAD调用

GLAD是管理OpenGL的函数指针的，因此在调用任何OpenGL的函数之前我们都需要初始化GLAD

我们需要给GLAD传入用来**加载系统相关的OpenGL函数指针地址的函数**，GLFW给我们提供的是glfwGetProcAddress

```c++
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return-1;
}
```

## 视口

我们必须给OpenGL提供渲染窗口的尺寸大小，这样OpenGL才能知道怎样根据窗口大小来显示数据和坐标。

```c++
// 窗口位置X，窗口位置Y，窗口宽度，窗口高度
glViewport(0, 0, 800, 600);
```

OpenGL幕后使用的glViewport中定义的位置和宽高进行2D坐标的转换，将OpenGL中的位置坐标转换为你的屏幕坐标。

>例如，OpenGL中的坐标(-0.5, 0.5)有可能（最终）被映射为屏幕中的坐标(200,450)。注意，处理过的OpenGL坐标范围只为-1到1，因此我们事实上将(-1到1)范围内的坐标映射到(0, 800)和(0, 600)。

用户在改变窗口大小的时候，视口也应该被调整，我们可以对窗口注册一个回调函数，它会在每次窗口大小被调用的时候被调用，每当窗口改变大小的时候，GLFW就会调用这个函数并填充相应的参数供你使用。

```c++
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
```

但是我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数

```c++
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

我们就可以通过这种方式来处理各种变化，比如手柄输入变化，处理错误消息等等。

## 渲染循环

我们并不希望绘制一个图像之后我们的应用程序就立即退出并关闭窗口，我们希望程序能够不断绘制图像并能够接受用户的输入。

我们要创造一个渲染循环，在我们推出GLFW之前一直保持运行。

```c++
while(!glfwWindowShouldClose(window))
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

- glfwWindowShouldClose函数在我们每次循环的**开始前检查一次GLFW是否被要求退出**，如果是的话，该函数返回`true`，渲染循环将停止运行，之后我们就可以关闭应用程序。
- glfwPollEvents**函数检查有没有触发什么事件**（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
- glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。

### 关于双缓冲

应用程序使用单缓冲绘图时可能**会存在图像闪烁**的问题。 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的。最终图像不是在瞬间显示给用户，而是通过一步一步生成的，这会导致渲染的结果很不真实。为了规避这些问题，我们应用双缓冲渲染窗口应用程序。**前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制**。当所有的**渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲**，这样图像就立即呈显出来，之前提到的不真实感就消除了。

## 释放资源

```c++
glfwTerminate();
return 0;
```

## Hello OpenGL

![image-20241202174407764](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202174407764.png)

## 输入

我们希望能够在GLFW中实现一些输入，可以通过使用GLFW的几个输入函数来完成

比如我们来检验用户是否按下了(ESC)

```c++
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

while (!glfwWindowShouldClose(window))
{
    processInput(window); // Add here.
    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

## 渲染

我们要将所有的渲染指令放在渲染循环之中，现在简单设置一个

```c++
glClearColor(0.2f,0.3f,0.3f,1.0f); // 状态设置函数
glClear(GL_COLOR_BUFFER_BIT); // 状态使用函数
```

我们可以通过调用glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲。

可能的缓冲位有

`GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT`

由于现在我们只关心颜色值，所以我们只清空颜色缓冲。

除了glClear之外，我们还调用了glClearColor来设置清空屏幕所用的颜色。

当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。

在这里，我们将屏幕设置为了类似黑板的深蓝绿色。

# 3.Hello,Triangle

- 顶点数组对象：Vertex Array Object，VAO
- 顶点缓冲对象：Vertex Buffer Object，VBO
- 元素缓冲对象：Element Buffer Object，EBO 或 索引缓冲对象 Index Buffer Object，IBO

在OpenGL中，任何事物都在3D空间中，而屏幕和窗口却是2D像素数组，3D坐标转为2D坐标的处理过程是由OpenGL的**图形渲染管线**

>指的是一堆原始图形数据途径一个输送管道，期间经过各种变化处理最终出现在屏幕的过程

图形管线的部分划分

+ 将3D坐标转换为2D坐标

+ 将2D坐标转变为实际的有颜色的像素

  >坐标和像素是不同的，坐标指的是精确的位置，而像素受到屏幕/窗口分辨率的限制

图形渲染管线每个阶段将会把前一个阶段的输出作为输入。所有这些阶段都是高度专门化的，并且很容易并行执行。

正是由于它们具有并行执行的特性，当今大多数显卡都有成千上万的小处理核心，它们在GPU上为每一个（渲染管线）阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些**小程序叫做着色器(Shader)**，OpenGL着色器是用OpenGL着色器语言（OpenGL Shading Language）来写成的。

![image-20241202182701861](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202182701861.png)

PS:蓝色部分为可修改环节。

## 渲染管线的工作方式

![image-20241202182701861](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202182701861.png)

我们以数组的形式传递3个3D坐标作为图形渲染管线的输入，用来表示一个三角形，这个数组叫做**顶点数据**(Vertex Data)。

顶点数据是一系列顶点的集合。一个顶点(Vertex)是一个3D坐标的数据的集合。**而这样一个顶点的数据是用顶点属性**(Vertex Attribute)表示的，它**可以包含任何我们想用的数据**，简单起见，我们先假定每个顶点只由一个3D位置和一些颜色值组成的。

为了让OpenGL知道我们的坐标和颜色值构成的到底是什么，OpenGL需要你去**指定这些数据所表示的渲染类型**。

我们是希望把这些数据渲染成一系列的点？一系列的三角形？还是仅仅是一个长长的线？做出的这些提示叫做**图元(Primitive)**。任何一个绘制指令的调用都将把图元传递给OpenGL。这是其中的几个：GL_POINTS、**GL_TRIANGLES**、GL_LINE_STRIP。

---

### 顶点着色器

**顶点着色器**，把单独的顶点作为输入，顶点着色器的主要的目的是把3D坐标转换为另一种3D坐标，同时允许我们对顶点属性进行一些基本处理。

### 几何着色器

顶点着色器阶段的输出可以选择性地传递给**几何着色器**(Geometry Shader)。**几何着色器将一组顶点作为输入，这些顶点形成图元**，并且能够**通过发出新的顶点来形成新的(或其他)图元**来生成其他形状。在这个例子中，它从给定的形状中生成第二个三角形。

### 图元装配

**图元装配**(Primitive Assembly)阶段将顶点着色器（或几何着色器）输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并将**所有的点装配成指定图元的形状**；本节例子中是两个三角形。

### 光栅化阶段

图元装配阶段的输出会被传入**光栅化阶段**(Rasterization Stage)，这里它会把图元映射为最终屏幕上相应的像素，**生成供片段着色器(Fragment Shader)使用的片段(Fragment)**。

>OpenGL中的一个片段是OpenGL渲染一个像素所需要的所有的数据。
>
>同时在片段着色器运行之前会执行裁切(Clipping)。**裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。**

### 片段着色器

**片段着色器的主要目的是计算一个像素的最终颜色**，这也是所有OpenGL高级效果产生的地方。通常，**片段着色器包含3D场景的数据（比如光照、阴影、光的颜色等等）**，这些数据可以被用来计算最终像素的颜色。

### Alpha测试和混合阶段

在所有对应颜色值确定以后，最终的对象将会被传到最后一个阶段，我们叫做**Alpha测试和混合(Blending)阶段**。

这个阶段检测片段的对应的深度（和模板(Stencil)）值，用它们来判断这个像素是其它物体的前面还是后面，决定是否应该丢弃。

这个阶段也会检查alpha值（alpha值定义了一个物体的透明度）并对物体进行混合(Blend)。

所以，即使在片段着色器中计算出来了一个像素输出的颜色，在渲染多个三角形的时候最后的像素颜色也可能完全不同。

---

在现代的OpenGL中，我们必须定义至少一个顶点着色器和一个片段着色器。

## 顶点输入

```c++
float vertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
```

![image-20241202191643325](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202191643325.png)

OpenGL并不是简单地把所有的3D坐标变换为屏幕上的2D像素，OpenGL仅当3D坐标在三个轴上[-1,1]的范围内时才能处理它，在这个范围内的坐标叫做**标准化设备坐标**，在此范围以外的坐标则不会显示，（0，0是图像的中心）

>z坐标设置为0，三角形每一点的深度都是一样的。
>
>通常深度可以理解为z坐标，它代表一个像素在空间中和你的距离，如果离你远就可能被别的像素遮挡，你就看不到它了，它会被丢弃，以节省资源。

当顶点坐标已经在顶点着色器中处理过后，就应该是标准化设备坐标了。

通过使用由**glViewport**函数提供的数据，进行视口变换，**标准化设备坐标会变换为屏幕空间坐标**。

所得的**屏幕空间坐标又会被变换为片段输入到片段着色器**中。

---

定义这样的顶点数据以后，我们会把它作为输入发送给图形渲染管线的第一个处理阶段：**顶点着色器。**

它**会在GPU上创建内存用于储存我们的顶点数据**，还要配置OpenGL如何解释这些内存，并且指定其如何发送给显卡。顶点着色器接着会处理我们在内存中指定数量的顶点。

我们通过**顶点缓冲对象**（Vetex Buffer Object）来管理这个内存，它会在GPT内存中储存大量的顶点。

我们可以使用glGenBuffers函数生成一个带有缓冲ID的VBO对象：

```c++
unsigned int VBO;
glGenBuffers(1, &VBO);
```

OpenGL中有很多的缓冲对象类型，顶点缓冲对象的缓冲类型是`GL_ARRAY_BUFFER`，OpenGL允许我们同时绑定多个缓冲（只针对于不同的类型），我们可以通过glBindBuffer函数把新创建的缓冲绑定到`GL_ARRAY_BUFFER`上

```c++
glBindBuffer(GL_ARRAY_BUFFER, VBO);
```

绑定之后，我们使用的任何缓冲调用都会用来配置当前绑定的缓冲（VBO），我们可以调用**glBufferData函数**，来将之前定义的**顶点数据复制到缓冲的内存**中。

```c++
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

顶点缓冲对象当前绑定到`GL_ARRAY_BUFFER`目标上。第二个参数指定传输数据的大小(以字节为单位)；用一个简单的`sizeof`计算出顶点数据大小就行。第三个参数是我们希望发送的实际数据。

![image-20241202193015764](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202193015764.png)![image-20241202193028827](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241202193028827.png)



第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：

- GL_STATIC_DRAW ：数据不会或几乎不会改变。
- GL_DYNAMIC_DRAW：数据会被改变很多。
- GL_STREAM_DRAW ：数据每次绘制时都会改变。

现在我们就把顶点数据存储到了显卡之中了，用VBO这个顶点缓冲对象管理。

## 顶点着色器构造

对于现代OpenGL而言，如果我们打算做渲染的话，我们至少需要一个顶点着色器和一个片段着色器。

我们需要用着色器语言OpenGL Shading Langauge来编写顶点着色器，然后编译这个着色器，我们就可以在程序中使用了。

```c++
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

每个着色器都始于一个版本声明。

使用`in`关键字，在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)。

现在我们只关心位置(Position)数据，所以我们只需要一个顶点属性。

GLSL有一个向量数据类型，它包含1到4个`float`分量，包含的数量可以从它的后缀数字看出来。

由于每个顶点都有一个3D坐标，我们就创建一个`vec3`输入变量aPos。

我们同样也通过`layout (location = 0)`设定了输入变量的位置值(Location)你后面会看到为什么我们会需要这个位置值。

### 编译着色器

我们将顶点着色器的源代码硬编码在代码文件顶部的C风格字符串中：

```c++
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
```

创建着色器对象:

```c++
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
```

我们现在创造的是顶点着色器，所以传递的参数是`GL_VERTEX_SHADER`。

现在我们将这个着色器源码附加到着色器对象上，然后编译它

```c++
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

glShaderSource函数把要编译的着色器对象作为第一个参数。

第二参数指定了传递的源码字符串数量，这里只有一个。

第三个参数是顶点着色器真正的源码。

第四个参数我们先设置为`NULL`。

### 编译错误

如果编译失败的话，可能会希望知道错误是什么，才能修复。

```c++
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
```

我们定义一个整型变量来表示是否成功编译，还定义了一个储存错误消息（如果有的话）的容器。

然后我们用glGetShaderiv检查是否编译成功。

如果编译失败，我们会用glGetShaderInfoLog获取错误消息，然后打印它。

```c++
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << "ERROR:SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
}
```

## 片段着色器构造

片段着色器所做地是计算像素最后的颜色输出。

片段着色器只需要一个输出变量，用于表示最终的输出颜色。

```c++
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
```

```c++
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";
```

编译片段着色器和顶点着色器类似，但是我们使用GL_FRAGMENT_SHADER常量来作为着色器的类型

```c++
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error:SHADER:VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
    }
```

## 链接着色器对象

着色器程序对象（Shader **Program** Object） 是**多个着色器合并之后并最终链接完成的版本**，如果**要使用刚才编译的着色器我们必须把它们链接为一个着色器程序对象**，然后在**渲染对象的时候激活这个着色器程序**。已经激活的着色器程序的着色器将在我们发送渲染调用的时候被使用。

创建程序对象的方式如下：

```c++
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
```

然后将之前编译的着色器附加到程序对象上，然后用glLinkProgram来链接

```c++
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```

错误检测方法

```c++
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success)
{
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    ...
}
```

我们可以通过调用glUseProgram函数，将刚刚创建的程序对象作为它的参数，来激活这个程序对象

```c++
glUseProgram(shaderProgram);
```

调用之后，每个着色器调用和渲染都会使用这个程序对象。

注意在链接了着色器之后，就可以删除着色器了。

```c++
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

现在我们已经把输入的顶点数据发送给了GPU，并且指示了GPU如何在顶点和片段着色器中处理它。

但是**OpenGL目前还并不知道如何解释内存中的顶点数据**，以及该如何将顶点数据链接到顶点着色器的属性上。

## 链接顶点属性















