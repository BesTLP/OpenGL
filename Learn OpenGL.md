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
float vertices[] = {
       -0.5f, -0.5f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, // right 
        0.0f,  0.5f, 0.0f  // top   
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

顶点着色器允许我们指定任何以顶点属性为形式的输入，我们必须手动指定输入的哪一个部分对应顶点着色器的哪一个顶点属性。

我们必须在渲染之前就指定OpenGL如何解释这个顶点数据。

![image-20241203130546599](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241203130546599.png)

- 位置数据被储存为32位（4字节）浮点值。

  >```c++
  >sizeof(float) = 4;
  >```

- 每个位置包含3个这样的值。

- 在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列(Tightly Packed)。

- 数据中第一个值在缓冲开始的位置。

我们可以使用glVertexAttribPointer函数告诉OpenGL应该如何解析顶点数据。

```c++
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
```

![image-20241203131353824](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241203131353824.png)

第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用`layout(location = 0)`定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为`0`。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入`0`。

第二个参数指定顶点属性的大小。顶点属性是一个`vec3`，它由3个值组成，所以大小是3，所以如果是2D纹理值的话，就是2.

**每个顶点属性从一个VBO管理的内存中获得它的数据**，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用**glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。**由于在**调用glVertexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性`0`现在会链接到它的顶点数据。**

在 OpenGL 中，`glVertexAttribPointer` 函数的第一个参数指定了顶点属性的索引位置（index），即你在顶点着色器中使用 `layout(location = index)` 时指定的 `index`。

为什么这个 `index` 一定是 `0`，而不是其他的数字呢？这是因为你在顶点着色器中定义了特定的顶点属性，它们的 `index` 值由你在着色器中设置的 `layout(location = n)` 来控制。比如，定义位置属性时通常使用 `layout(location = 0)` 来指定 `position` 属性的索引为 0。

具体的例子如下：

```c++
#version 330 core

layout(location = 0) in vec3 position;   // 位置属性
layout(location = 1) in vec3 color;      // 颜色属性
layout(location = 2) in vec2 texCoord;   // 纹理坐标属性

void main() {
    gl_Position = vec4(position, 1.0);
}


// 绑定到位置0
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
glEnableVertexAttribArray(0);  // 激活位置属性

// 绑定到位置1
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
glEnableVertexAttribArray(1);  // 激活颜色属性

// 绑定到位置2
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
glEnableVertexAttribArray(2);  // 激活纹理坐标属性

```

**`size`**

- 指定每个顶点属性包含的分量数。可以是 1, 2, 3, 4。
  - 对于位置属性 `vec3 position;`，`size` 应为 3（表示三个浮动分量）。
  - 对于颜色属性 `vec4 color;`，`size` 应为 4（表示四个浮动分量）。

第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中`vec*`都是由浮点数值组成的)。

**`type`**

- 意义

  : 指定数组中每个组件的数据类型。常见的类型包括：

  - `GL_FLOAT`：表示浮动数据（如位置、法线、颜色等）。
  - `GL_INT`：表示整数数据（如纹理坐标）。
  - `GL_UNSIGNED_BYTE`：表示无符号字节数据。

- **例子**: 对于位置数据，通常使用 `GL_FLOAT`。

下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到**0（对于有符号型signed数据是-1）到1之间**。我们把它设置为GL_FALSE。

**`normalized`**

- **意义**: 如果为 `GL_TRUE`，表示将整数类型的值归一化到 [0,1] 或 [-1,1] 范围内。对于浮动数据，通常设置为 `GL_FALSE`。
- **例子**: 对于整数类型（如 `GL_BYTE` 或 `GL_UNSIGNED_BYTE`），通常使用归一化，以确保它们映射到浮动类型时保持有效范围。

第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个`float`之后，我们把步长设置为`3 * sizeof(float)`。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。

**`stride`**：
假设每个顶点包含了多个属性，比如**位置、纹理坐标、法向量**等。`stride`的作用是指定从一个顶点到下一个顶点的字节偏移量。假设你的顶点数据按以下结构存储：

- 3个 `float` 用来存储位置 (每个 `float` 占4字节，共12字节)
- 2个 `float` 用来存储纹理坐标 (共8字节)
- 3个 `float` 用来存储法向量 (共12字节)

所以每个顶点的总大小是：
`12 + 8 + 12 = 32` 字节

因此，`stride` 就是 `32` 字节，表示每个顶点的起始位置与下一个顶点的起始位置之间的距离。

最后一个参数的类型是`void*`，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。

**`pointer`**：
`pointer` 是指数据在缓冲区中的偏移量，指示从哪里开始读取数据。假设缓冲区中的顶点数据结构如前所示，从位置开始，按顺序存储位置、纹理坐标、法向量。如果我们设置：

- `pointer = 0`，表示从第一个 `float`（位置的第一个值）开始读取。
- `pointer = 12`，表示从纹理坐标的第一个值开始读取，因为位置占了12个字节。
- `pointer = 20`，表示从法向量的第一个值开始读取，因为纹理坐标占了8个字节。

---

那么现在我们已经定义了OpenGL应该如何解释顶点数据，我们之后使用glEnableVertexAttribArray，以顶点属性位置值作为参数

```c++
// 启用顶点属性
glEnableVertexAttribArray(0);  // 启用位置属性
glEnableVertexAttribArray(1);  // 启用颜色属性
glEnableVertexAttribArray(2);  // 启用纹理坐标属性

// 禁用顶点属性（可选）
glDisableVertexAttribArray(0);  // 禁用位置属性
glDisableVertexAttribArray(1);  // 禁用颜色属性
glDisableVertexAttribArray(2);  // 禁用纹理坐标属性
```

然后我们使用一个顶点缓冲对象将顶点数据初始化到缓冲当中，建立了一个顶点和一个片段着色器，并告诉了OpenGL如何把顶点数据链接到顶点着色器的属性上。

然后我们可以绘制物体了。

```c++

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizoef(floag), (void*)0);
glEnableVertexAttribArray(0);

glUseProgram(shaderProgram);

someOpenGLFuncationThatDrawsOurTriangle();

```

## 顶点数组对象

顶点数组对象（Vertex Array Object, VAO）可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中，好处是，配置顶点属性指针的时候，只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定对应的VAO即可。

使得不同顶点数据和属性配置之间的切换会变得非常简单，只需要绑定不同的VAO即可，刚刚设置的所有状态都将存储在VAO之中。

一个顶点数组对象会储存以下这些内容：

- glEnableVertexAttribArray和glDisableVertexAttribArray的调用。
- 通过glVertexAttribPointer设置的顶点属性配置。
- 通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象。

### 创建VAO

```c++
unsigned int VAO;
glGenVertexArrays(1, &VAO);
```

要想使用VAO，只是使用glBindVertexArray绑定VAO即可，绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用。当我们打算绘制一个物体的时候，我们只要在绘制物体前简单地将VAO绑定到希望使用地设定上即可

```c++
unsigned int VAO;
glGenVertexArray(1, &VAO);

// ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
// 1. 绑定VAO
glBindVertexArray(VAO);
// 2. 把顶点数组复制到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
// 4. 绘制物体
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();
```

当你打算绘制多个物体地时候，你首先要生成和配置所有地VAO（和必须的VBO及其属性指针），然后储存它们以供后面使用，当我们打算绘制物体的时候拿出相应的VAO，绑定它，然后绘制完物体之后，再解绑VAO。

### VBO 和 VAO

VBO是存储数据的工具。

VAO是管理如何使用这些数据的工具。

**绑定 VAO**：当你绑定 VAO 后，OpenGL 会知道接下来的所有状态配置都会被与这个 VAO 相关联。也就是说，任何顶点属性的配置、VBO 的绑定等都会被记录到当前绑定的 VAO 中。

**配置 VBO 和顶点属性**：接下来，你配置 VBO，上传数据到显存，并通过 `glVertexAttribPointer` 和 `glEnableVertexAttribArray` 来指定数据格式（如位置是 `vec3`，颜色是 `vec3`）。这些配置会被保存到 VAO 中。

**解绑 VAO 和 VBO**：绑定 VAO 后，你通常会解绑 VBO 和 VAO，这样做是为了不让它们对其他部分产生影响。

比如一个多个VBO和一个VAO的例子：

```c++
GLuint VBOs[3], VAO;
glGenBuffers(3, VBOs);  // 生成 3 个 VBO
glGenVertexArrays(1, &VAO);  // 生成一个 VAO

// 绑定 VAO
glBindVertexArray(VAO);

// 1. 绑定位置数据到第一个 VBO
glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 设置位置属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// 2. 绑定颜色数据到第二个 VBO
glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 设置颜色属性指针
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

// 3. 绑定法线数据到第三个 VBO
glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 设置法线属性指针
glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

// 解绑 VBO 和 VAO
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

// 绑定 VAO 并绘制立方体
glBindVertexArray(VAO);
glDrawArrays(GL_QUADS, 0, 8);  // 立方体有 8 个顶点
glBindVertexArray(0);

```

## 三角形绘制

```C++
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
```

我们希望绘制的是一个三角形，这里传递GL_TRIANGLES给它。第二个参数指定了顶点数组的起始索引，我们这里填`0`。最后一个参数指定我们打算绘制多少个顶点，这里是`3`（我们只从我们的数据中渲染一个三角形，它只有3个顶点长）。

完整的代码如下:

```c++
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// c++
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
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
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 创建着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error:SHADER:VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
	}

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

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error:ShaderProgram::LinkError:" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		   -0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 传输顶点信息
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置函数
		glClear(GL_COLOR_BUFFER_BIT); // 状态使用函数

		processInput(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
```

## 元素缓冲对象

渲染顶点的最后一个话题，元素缓冲对象（Element Buffer Object）也叫索引缓冲对象(Index Buffer Object, IBO)。

假设我们不再绘制一个三角形而是一个矩形，那么我们可以通过绘制两个三角形来组成一个矩形。

```c++
float vertices[] = {
    // 第一个三角形
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, 0.5f, 0.0f,  // 左上角
    // 第二个三角形
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
```

实际上我们可以不用存储六个顶点，而是存储四个顶点，然后指定绘制的顺序就可以了，这种索引绘制就是我们想要的方式

```c++
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};
```

### 创建EBO

```c++
unsigned int EBO;
glGenBuffers(1, &EBO);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

我们传递了GL_ELEMENT_ARRAY_BUFFER当作缓冲目标。

最后一件要做的事是用**glDrawElements来替换glDrawArrays函数**，表示我们要从索引缓冲区渲染三角形。使用glDrawElements时，我们会使用当前绑定的索引缓冲对象中的索引进行绘制： 

```c++
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

第一个参数指定了我们绘制的模式，这个和glDrawArrays的一样。第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。第三个参数是索引的类型，这里是GL_UNSIGNED_INT。最后一个参数里我们可以指定EBO中的偏移量（或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候），但是我们会在这里填写0。

但实际上，这个绑定EBO的操作也可以放在VAO之中。

```c++
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// 记得后面绘制的时候要替换成glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

![image-20241203140927372](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241203140927372.png)

+ 开启线框模式的方法`glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);`

  >第一个参数表示我们打算将其应用到所有的三角形的正面和背面，第二个参数告诉我们用线来绘制。

## 第三章练习题

1.添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形(着色器部分就省略了)

```c++
float vertices[] = {
	-0.5f,-0.5f,0,
	-0.5f,0.5f,0,
	0.5f,-0.5f,0,
	-0.5f,0.5f,0,
	0.5f,0.5f,0,
	0.5f,-0.5f,0
};

unsigned int VAO, VBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
while (!glfwWindowShouldClose(window))
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置函数
	glClear(GL_COLOR_BUFFER_BIT); // 状态使用函数

	processInput(window);

	glBindVertexArray(VAO);
	glUseProgram(shaderProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

```

2.创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO：

```c++
// 定义两个三角形的顶点数据
float firstTriangle[] = {
	-0.5f, -0.5f, 0.0f,  // 第一个三角形的第一个顶点
	-0.5f,  0.5f, 0.0f,  // 第一个三角形的第二个顶点
	 0.5f, -0.5f, 0.0f   // 第一个三角形的第三个顶点
};

float secondTriangle[] = {
	-0.5f, -0.5f, 0.0f,  // 第一个三角形的第一个顶点
	-0.5f,  0.5f, 0.0f,  // 第一个三角形的第二个顶点
	 0.5f, -0.5f, 0.0f   // 第一个三角形的第三个顶点
};

// 定义 VAO 和 VBO 数组
unsigned int VBO[2], VAO[2];

// 生成 VAO 和 VBO
glGenBuffers(2, VBO);
glGenVertexArrays(2, VAO);

// 配置第一个三角形的 VAO 和 VBO
glBindVertexArray(VAO[0]);
glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);  // 解绑 VBO

// 配置第二个三角形的 VAO 和 VBO
glBindVertexArray(VAO[1]);
glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);  // 解绑 VBO

glBindVertexArray(0);  // 解绑 VAO
while (!glfwWindowShouldClose(window))
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置函数
	glClear(GL_COLOR_BUFFER_BIT); // 状态使用函数

	processInput(window);
	glUseProgram(shaderProgram);
	// 绘制第一个三角形
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);  // 绘制第一个三角形

	// 绘制第二个三角形
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);  // 绘制第二个三角形

	glfwSwapBuffers(window);
	glfwPollEvents();
}
```

3.创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色（1，1，0，1）：

```c++
#version 330 core
out vec4 FragColorYellow;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 0, 1.0f);
}
```

```c++
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
char infoLog[512];
int success;
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

if (!success)
{
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << infoLog << std::endl;
}

unsigned int fragmentShader1, fragmentShader2;
fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
glad_glCompileShader(fragmentShader1);
glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
if (!success)
{
	glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
	std::cout << infoLog << std::endl;
}

fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
glCompileShader(fragmentShader2);
glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
if (!success)
{
	glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
	std::cout << infoLog << std::endl;
}

unsigned int shaderProgram1, shaderProgram2;
shaderProgram1 = glCreateProgram();
shaderProgram2 = glCreateProgram();

glAttachShader(shaderProgram1, vertexShader);
glAttachShader(shaderProgram1, fragmentShader1);
glAttachShader(shaderProgram2, vertexShader);
glAttachShader(shaderProgram2, fragmentShader2);

glLinkProgram(shaderProgram1);
glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
if (!success)
{
	glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
	std::cout << infoLog << std::endl;
}
glLinkProgram(shaderProgram2);

glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
if (!success)
{
	glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
	std::cout << infoLog << std::endl;
}

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader1);
glDeleteShader(fragmentShader2);

float firstTriangle[] = {
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
};
float secondTriangle[] = {
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
};

// 定义 VAO 和 VBO 数组
unsigned int VBO[2], VAO[2];

// 生成 VAO 和 VBO
glGenBuffers(2, VBO);
glGenVertexArrays(2, VAO);

// 配置第一个三角形的 VAO 和 VBO
glBindVertexArray(VAO[0]);
glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);  // 解绑 VBO

// 配置第二个三角形的 VAO 和 VBO
glBindVertexArray(VAO[1]);
glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);  // 解绑 VBO

glBindVertexArray(0);  // 解绑 VAO
while (!glfwWindowShouldClose(window))
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置背景色
	glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓存

	processInput(window);

	// 绘制第一个三角形（红色）
	glUseProgram(shaderProgram1);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// 绘制第二个三角形（绿色）
	glUseProgram(shaderProgram2);
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwSwapBuffers(window);
	glfwPollEvents();
}
```

# 4.着色器

着色器(Shader)是运行在GPU上的小程序。这些小程序为图形渲染管线的某个特定部分而运行。从基本意义上来说，着色器只是一种把输入转化为输出的程序。着色器也是一种非常独立的程序，因为它们之间不能相互通信；它们之间唯一的沟通只有通过输入和输出。

## GLSL

着色器是使用一种叫做GLSL的类C语言编写的，GLSL是为图形计算量身定制的，包含了一些针对向量和矩阵操作的有用特性。

```c
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

void main()
{
  // 处理输入并进行一些图形操作
  ...
  // 输出处理过的结果到输出变量
  out_variable_name = weird_stuff_we_processed;
}
```

当谈论顶点着色器的时候，每个输入变量也叫做顶点属性，我们能声明的顶点属性是有上限的，一般是由硬件来决定的。

OpenGL确保了至少有16个包含4分量的顶点属性可用。

```c++
int nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
```

## 数据类型

包含C语言中的基础数据类型：`int`, `float`, `double`, `uint`, `bool`.

GLSL也有两种容器类型：`Vector`, `Matrix`

GLSL中的向量可以包含了2-4个分量的容器。

| 类型    | 含义                                             |
| :------ | :----------------------------------------------- |
| `vecn`  | 包含`n`个float分量的默认向量（大多数情况下使用） |
| `bvecn` | 包含`n`个bool分量的向量                          |
| `ivecn` | 包含`n`个int分量的向量                           |
| `uvecn` | 包含`n`个unsigned int分量的向量                  |
| `dvecn` | 包含`n`个double分量的向量                        |

向量这一数据类型也允许一些有趣而灵活的分量选择方式，叫做重组(Swizzling)。重组允许这样的语法：

```c++
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
```

你可以使用上面4个字母任意组合来创建一个和原来向量一样长的（同类型）新向量，只要原来向量有那些分量即可；然而，你不允许在一个`vec2`向量中去获取`.z`元素。我们也可以把一个向量作为一个参数传给不同的向量构造函数，以减少需求参数的数量：

```c++
vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);
```

## 输入与输出

着色器虽然是各自独立的小程序，但是都是整体的一部分，GLSL定义了in和out关键字专门来实现这个目的，只要一个输出变量与下一个着色器阶段的输入匹配，就会传递下去，**但在顶点和片段着色器中会有点不同。**

顶点着色器应该接收的是一种特殊形式的输入，否则就会效率低下。**顶点着色器的输入特殊在，它从顶点数据中直接接收输入**。为了**定义顶点数据该如何管理，我们使用`location`这一元数据指定输入变量，这样我们才可以在CPU上配置顶点属性**。我们已经在前面的教程看过这个了，`layout (location = 0)`。顶点着色器需要为它的输入提供一个额外的`layout`标识，这样我们才能把它链接到顶点数据。

片段着色器，需要一个`vec4`颜色输出变量，如果片段着色器没有定义输出的颜色，那么OpenGL就会把物体渲染为`black` or`white`。

我们可以修改之前的顶点着色器和片段着色器，让顶点着色器为片段着色器确定颜色

```c++
// 顶点着色器
#version 330 core
layour(location = 0) in vec3 aPos;

out vec4 vertexColor;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(0.5,0,0,1);
}
```

```c++
// 片段着色器
#version 330 core
// 先in还是先out不区分
out vec4 FragColor;

in vec4 vertexColor;
void main()
{
    FragColor = vertexColor;
}
```

```c++
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = vec4(0.5, 0, 0, 1);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"FragColor = vertexColor;\n"
"}\n";
```

## Uniform

Uniform是从应用程序在CPU上传递数据到GPU上的着色器的方式。

但uniform和顶点属性有些不同。首先，uniform**是全局的(Global)**。全局意味着uniform变量必须在每个着色器程序对象中都是独一无二的，而且它可以被着色器程序的任意着色器在任意阶段访问。第二，无论你把uniform值设置成什么，uniform会一直保存它们的数据，直到它们被重置或更新。

要在 GLSL 中声明 uniform，我们只需在着色器中使用 `uniform` 关键字，并带上类型和名称。从那时起，我们就可以在着色器中使用新声明的 uniform。我们来看看这次是否能通过uniform设置三角形的颜色：

```c++
#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量

void main()
{
    FragColor = ourColor;
}
```

因为uniform是全局变量，因此我们可以在任何着色器中去定义它们，而不需要通过顶点着色器作为中介，顶点着色器中不需要这个uniform，所以我们不用在那里定义。

+ 如果你声明了一个uniform却在GLSL代码中没用过，编译器会静默移除这个变量，**导致最后编译出的版本中并不会包含它，这可能导致几个非常麻烦的错误，记住这点**！

我们可以通过寻找着色器中uniform属性的位置值，然后来更新它

```c++
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    float redValue = sin(timeValue) / 4.0f + 0.75f;
    float blueValue = sin(timeValue) / 5.0f + 0.8f;

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
```

我们用glGetUniformLocation查询uniform ourColor的位置值。

我们为查询函数提供着色器程序和uniform的名字（这是我们希望获得的位置值的来源）。如果glGetUniformLocation**返回`-1`就代表没有找到这个位置值**。

最后，我们可以通过glUniform4f函数设置uniform值。注意，查询uniform地址不要求你之前使用过着色器程序。

**更新一个uniform之前你必须先使用程序**（调用glUseProgram)，因为它是在当前激活的着色器程序中设置uniform的。

因为OpenGL在其核心是一个C库，所以**它不支持类型重载**，在函数参数不同的时候就要为其定义新的函数；glUniform是一个典型例子。这个函数有一个特定的后缀，标识设定的uniform的类型。可能的后缀有：

| 后缀 | 含义                                 |
| :--- | :----------------------------------- |
| `f`  | 函数需要一个float作为它的值          |
| `i`  | 函数需要一个int作为它的值            |
| `ui` | 函数需要一个unsigned int作为它的值   |
| `3f` | 函数需要3个float作为它的值           |
| `fv` | 函数需要一个float向量/数组作为它的值 |

每当你打算配置一个OpenGL的选项时就可以简单地根据这些规则选择适合你的数据类型的重载函数。在我们的例子里，**我们希望分别设定uniform的4个float值，所以我们通过glUniform4f传递我们的数据**(注意，我们也可以使用`fv`版本)。

## 更多的属性

我们尝试直接将颜色的属性也加入到`vertices`数组之中

```c++
float vertices[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};
```

我们就要修改相应的顶点着色器

```c++
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 outColor;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    outColor = aColor;
}
```

还有片段着色器

```c++
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
```

![image-20241203164028386](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241203164028386.png)

现在的位置信息就需要得到更新

```c++
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)3 * sizeof(float));
glEnableVertexAttribArray(1);
```

由于我们现在有了两个顶点属性，我们不得不重新计算**步长**值。

为获得数据队列中下一个属性值（比如位置向量的下个`x`分量）我们必须向右移动6个float。其中3个是位置值，另外3个是颜色值。这使我们的步长值为6乘以float的字节数（=24字节）。

同样，这次我们必须指定一个偏移量。对于每个顶点来说，位置顶点属性在前，所以它的偏移量是0。颜色属性紧随位置数据之后，所以偏移量就是`3 * sizeof(float)`，用字节来计算就是12字节。

![image-20241203164837519](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241203164837519.png)

这是在片段着色器中进行的所谓**片段插值**(Fragment Interpolation)的结果。

当渲染一个三角形时，**光栅化(Rasterization)阶段**通常会造成比原指定顶点更多的片段。

光栅会根据每个片段在三角形形状上所处相对位置决定这些片段的位置。

基于这些位置，它会**插值**(Interpolate)所有片段着色器的输入变量。

**插值**就是通过计算每个片段距离三角形各个角的远近，来决定它的颜色。比如：

- 如果片段离左上角很近，它的颜色就会是**绿色**。
- 如果片段离右上角很近，它的颜色就会是**蓝色**。
- 如果片段离底部很近，它的颜色就会是**红色**。

## 构建我们自己的着色器类

我们可以写一个类，让它从硬盘来读取着色器，然后编译并链接并进行错误检测。

```c++
#ifndef SHADER_H // 常用的防止头文件重复包含的预处理指令
#define SHADER_H

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};

#endif
```

**题外话：**

+ `#ifndef SHADER_H`：`ifndef` 代表 "if not defined"，意思是如果 `SHADER_H` 这个宏没有被定义过，就会执行接下来的代码。

  `#define SHADER_H`：这行定义了 `SHADER_H` 宏，表示这个头文件已经被包含过了。

  `#endif`：标记条件编译结束。这个指令结束了 `#ifndef` 的条件语句。

## 第四章练习题

修改顶点着色器让三角形上下颠倒：[参考解答](https://learnopengl.com/code_viewer.php?code=getting-started/shaders-exercise1)

让y轴上下颠倒即可

```c++
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
"ourColor = vec3(aColor);\n"
"}\n";
```

使用uniform定义一个水平偏移量，在顶点着色器中使用这个偏移量把三角形移动到屏幕右侧：[参考解答	](https://learnopengl.com/code_viewer.php?code=getting-started/shaders-exercise2)

```c++
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"uniform float offset;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x + offset, aPos.y + offset, aPos.z + offset, 1.0);\n"
"ourColor = vec3(aColor);\n"
"}\n";

int uniformOffsetLocation = glGetUniformLocation(shaderProgram, "offset");
if (uniformOffsetLocation == -1)
{
    return -1;
}
float offset = std::min(glfwGetTime(), 0.5);
glUniform1f(uniformOffsetLocation, offset);
```

使用`out`关键字把顶点位置输出到片段着色器，并将片段的颜色设置为与顶点位置相等（来看看连顶点位置值都在三角形中被插值的结果）。做完这些后，尝试回答下面的问题：为什么在三角形的左下角是黑的?：[参考解答](https://learnopengl.com/code_viewer.php?code=getting-started/shaders-exercise3)

```c++
#version 330 core

// 输入顶点属性
layout(location = 0) in vec3 aPos;    // 顶点位置
layout(location = 1) in vec3 aColor;  // 顶点颜色

// Uniform变量，用于在应用程序和着色器之间传递数据
uniform float offset;                 // 偏移量

// 输出到片段着色器的颜色数据
out vec3 ourColor;                    // 传递给片段着色器的颜色
out vec3 ourPos;

void main()
{
    // 设置顶点位置，并应用偏移量
    gl_Position = vec4(aPos.x + offset, aPos.y + offset, aPos.z + offset, 1.0);
    
    // 将颜色传递给片段着色器
    ourPos = vec3(aPos);
    ourColor = vec3(aColor);
};

```

```c++
#version 330 core

in vec3 ourColor;  // 从顶点着色器接收的颜色数据
in vec3 ourPos;
out vec4 FragColor;  // 片段着色器的输出颜色

void main()
{
    FragColor = vec4(ourPos, 1.0);  // 将接收到的颜色值转换为 vec4，并设置 alpha 为 1.0（不透明）
};

```

如果你希望颜色值正常插值，确保在顶点着色器中传递的颜色属性在 `[0.0f, 1.0f]` 范围内。

片段颜色的输出等于三角形。我们的三角形左下角点的坐标是多少？这是 （-0.5f， -0.5f， 0.0f）。由于 xy 值为负，它们被限制为 0.0f 的值。

# 5.纹理

纹理是一个2D图片（也可以有1D和3D），可以用来添加物体的细节。

![image-20241204143923867](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204143923867.png)

为了将纹理映射到三角形上，我们需要指定三角形的**每个顶点各自对应纹理的哪个部分，这样每个顶点都会关联一个纹理坐标**，用来**标明该从纹理图像的哪个部分来采样**，之后在图形的其它片段上进行片段插值(Fragment Interpolation)。

纹理坐标在x和y轴上，范围为0到1之间（注意我们使用的是2D纹理图像）。使用纹理坐标获取纹理颜色叫做采样(Sampling)。**纹理坐标起始于(0, 0)，也就是纹理图片的左下角，终止于(1, 1)，即纹理图片的右上角**。

因此我们为三角形指定3个纹理坐标点。

```c++
float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f  // 上中
};
```

z河阳三角形的左下角就对应纹理的左下角，其余点同理。

传递到片段着色器中，就会为每个片段都进行纹理坐标的插值。

## 纹理环绕方式

纹理坐标的**范围通常是从(0, 0)到(1, 1)**，如果我们把纹理坐标设置在**范围之外，OpenGL默认的行为是重复这个纹理图像**（我们基本上忽略浮点纹理坐标的整数部分）

| 环绕方式           | 描述                                                         |
| :----------------- | :----------------------------------------------------------- |
| GL_REPEAT          | 对纹理的默认行为。重复纹理图像。                             |
| GL_MIRRORED_REPEAT | 和GL_REPEAT一样，但每次重复图片是镜像放置的。                |
| GL_CLAMP_TO_EDGE   | 纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。 |
| GL_CLAMP_TO_BORDER | 超出的坐标为用户指定的边缘颜色。                             |

![image-20241204144349628](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204144349628.png)

我们可以使用`glTexParameter*`函数对单独的一个坐标轴来设置选项s,t,r和x，y，z都是等价的

WRAP就是环绕的意思。

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
```

我们选择GL_CLAMP_TO_BORDER选项，我们还需要指定一个边缘的颜色。这需要使用glTexParameter函数的`fv`后缀形式，用GL_TEXTURE_BORDER_COLOR作为它的选项，并且传递一个float数组作为边缘的颜色值：

```c++
float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
```

## 纹理过滤

>你可以想象你打开一张`.jpg`格式图片，不断放大你会发现它是由无数像素点组成的，这个点就是纹理像素；注意不要和纹理坐标搞混。
>
>纹理坐标是你给模型顶点设置的那个数组，OpenGL以这个顶点的纹理坐标数据去查找纹理图像上的像素，然后进行采样提取纹理像素的颜色。
>
>纹理坐标通常是浮点值，但是纹理图像的分辨率通常是离散的，所以纹理坐标并不会精确地对应到纹理中的某一个像素点，就需要通过纹理过滤来处理这种不精确的情况。

纹理坐标并不依赖于分辨率，可以是任意的浮点值，所以OpenGL需要知道怎样将纹理像素映射到纹理坐标。

当你拥有一个很大的物体但是纹理的分辨率很低的时候，就要使用纹理过滤功能

+ GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式。

  ![image-20241204145547781](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204145547781.png)

+ GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。一个纹理像素的中心距离纹理坐标越近，那么这个纹理像素的颜色对最终的样本颜色的贡献越大。

  ![image-20241204145612212](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204145612212.png)

在一个很大的物体上应用一张低分辨率的纹理。

![image-20241204145705635](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204145705635.png)

使用`GL_NEAREST`会产生颗粒状的图案，我们能够清晰看到组成纹理的像素，但是`GL_LINEAR`能够产生更加平滑的图案，很难看出单个的纹理像素，可以产生更加真实的输出。

我们执行**放大**或者**缩小**操作的时候，可以设置纹理过滤的选项，比如缩小的时候使用临近过滤，而放大的时候使用线性过滤。

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

## 多级渐远纹理

观察者的距离超过一个阈值，OpenGL就会使用不同的多级渐远纹理，选择最适合物体的距离的那个。

![image-20241204150248812](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204150248812.png)

OpenGL自身提供了对应的函数`glGenerateMipmap`，能够自动创建多级渐远纹理。

> Mipmap 是一组逐渐减少分辨率的纹理级别，通常用于提高渲染效率和纹理质量，尤其是在进行纹理缩小时。

但是在渲染中切换多级渐远纹理级别的时候，不同级别的多级渐远纹理之间会产生不真实的生硬边界，就像普通的纹理过滤一样。

因此在切换多级渐远纹理的级别时，也可以在不同多级渐远纹理级别之间使用`NEAREST`和`LINEAR`过滤。

| 过滤方式                  | 描述                                                         |
| :------------------------ | :----------------------------------------------------------- |
| GL_NEAREST_MIPMAP_NEAREST | 使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样 |
| GL_LINEAR_MIPMAP_NEAREST  | 使用最邻近的多级渐远纹理级别，并使用线性插值进行采样         |
| GL_NEAREST_MIPMAP_LINEAR  | 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样 |
| GL_LINEAR_MIPMAP_LINEAR   | 在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样 |

很明显，只有在缩小过滤的情况之下，才能应用多级**渐远**纹理过滤选项，否则会报错`GL_INVALID_ENUM`

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

## 加载和创建纹理

我们可以用`stb_image.h`库来进行图像加载。

`stb_image.h`能够加载大部分流行的文件格式，并且能够很简单得整合到你的工程之中。`stb_image.h`可以在[这里](https://github.com/nothings/stb/blob/master/stb_image.h)下载。下载这一个头文件，将它以`stb_image.h`的名字加入你的工程，并另创建一个新的C++文件，输入以下代码：

```c++
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，等于是将这个头文件变为一个 `.cpp` 文件了。现在只需要在你的程序中包含`stb_image.h`并编译就可以了。

我们使用`stbi_load`函数就可以加载这个文件了。

```c++
int width, height, nrChannels;

unsigned char *data=  stbi_load("Image_Path", &width, &height, &nrChannels, 0);
```

这个函数首先接受一个图像文件的位置作为输入。

接下来它需要三个`int`作为它的第二、第三和第四个参数，`stb_image.h`将会用图像的**宽度**、**高度**和**颜色通道的个数**填充这三个变量。我们之后生成纹理的时候会用到的图像的宽度和高度的。

```c++
std::filesystem::path texturePath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "Figure" / "container.jpg";
int width, height, nrChannels;
unsigned char* data = stbi_load(texturePath.string().c_str(), &width, &height, &nrChannels, 0);

```

## 生成纹理

和之前OpenGL对象的生成一样，纹理也是使用ID来引用的。

```c++
unsigned int texture;
glGenTextures(1, &texture);
```

同样的生成之后我们需要绑定。

```c++
glBindTexture(GL_TEXTURE_2D, texture);
```

纹理可以通过`glTexImage2D`来生成

```c++
glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
```

- 第一个参数指定了纹理目标(Target)。**设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理**（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
- 第二个参数为**纹理指定多级渐远纹理的级别**，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是**基本级别**。
- 第三个参数告诉OpenGL我们**希望把纹理储存为何种格式**。我们的图像只有`RGB`值，因此我们也把纹理储存为`RGB`值，也就是**内部存储格式**。
- 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
- 下个参数应该总是被设为`0`（历史遗留的问题）。
- 第七第八个参数定义了源图的格式和数据类型。我们使用**RGB值加载**这个图像，并把它们**储存为`char`(byte)数组**，我们将会传入对应值。
- 最后一个参数是真正的图像数据。

当调用`glTexImage2D`时，当前绑定的纹理对象就会被附加上纹理图像，如果要使用多级纹理的话，那么必须手动设置不同的图像（不断来底层第二个参数），或者在自动生成纹理之后调用`glGenerateMipmap`，这会为当前绑定的纹理自动生成所有需要的多级渐远纹理

当生成了纹理和相应的多级渐远纹理之后，就需要释放内存了。

```c++
stbi_image_free(data);
```

---

整个流程如下所示：

```c++
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
// 为当前绑定的纹理对象设置环绕、过滤方式
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 加载并生成纹理
int width, height, nrChannels;
unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
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
```

## 应用纹理

我们需要告知OpenGL如何采样纹理，所以必须更新纹理坐标顶点数据

>因为这里的纹理坐标是2D的，所以只有两个`float`数值，所以是size = 2 

```c++
// 设置纹理坐标属性
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);
```

```c++
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
};
```

片段着色器接下来就会把输出变量`TexCoord`作为输入变量，关键是我们怎么将纹理对象传递给片段着色器呢？GLSL有一个供纹理对象使用的内建数据结构，叫做采样器(Sampler)。

比如`sampler1D`、`sampler3D`，或在我们的例子中的`sampler2D`。我们可以简单声明一个`uniform sampler2D`把一个纹理添加到片段着色器中。

我们使用GLSL内建的`texture`函数来采样纹理的颜色，它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。`texture`函数会使用之前设置的纹理参数对相应的颜色值进行采样。这个片段着色器的输出就是纹理的（插值）纹理坐标上的(过滤后的)颜色。

```c++
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}
```

![image-20241204164930990](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204164930990.png)

![image-20241204165038880](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204165038880.png)

完整代码：

```c++
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../../../headfile/Shader/Shader.h>
#include "../../../headfile/stb_image/stb_image.h"
// c++
#include <iostream>
#include <algorithm>

// file
#include <filesystem>

#define SOLUTION_DIR "D:\\repo\\OpenGL\\OpenGL"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
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
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//float vertices[] = {
	//	   -0.5f, -0.5f, 0.0f, // left  
	//		0.5f, -0.5f, 0.0f, // right 
	//		0.0f,  0.5f, 0.0f  // top   
	//};

	//float vertices[] = {
	//0.5f, 0.5f, 0.0f,   // 右上角
	//0.5f, -0.5f, 0.0f,  // 右下角
	//-0.5f, -0.5f, 0.0f, // 左下角
	//-0.5f, 0.5f, 0.0f   // 左上角
	//};

	//unsigned int indices[] = {
	//	// 注意索引从0开始! 
	//	// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
	//	// 这样可以由下标代表顶点组合成矩形

	//	0, 1, 3, // 第一个三角形
	//	1, 2, 3  // 第二个三角形
	//};

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	// 生成 VAO, VBO, EBO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 绑定 VAO
	glBindVertexArray(VAO);

	// 绑定 VBO 并传入数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 绑定 EBO 并传入数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 设置位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 设置颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 设置纹理坐标属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 组合解决方案目录和相对路径
	std::filesystem::path vertexPath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "ShaderSource" / "Chapter_5_Texture" / "Shader_5.vs";
	std::filesystem::path fragmentPath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "ShaderSource" / "Chapter_5_Texture" / "Shader_5.fs";

	// 获取绝对路径
	std::filesystem::path vertexAbsolutePath = std::filesystem::absolute(vertexPath);
	std::filesystem::path fragmentAbsolutePath = std::filesystem::absolute(fragmentPath);

	Shader shader(vertexAbsolutePath.string().c_str(), fragmentAbsolutePath.string().c_str());

	// 生成纹理对象
	std::filesystem::path texturePath = std::filesystem::path(SOLUTION_DIR) / "OpenGL" / "Figure" / "container.jpg";

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置函数
		glClear(GL_COLOR_BUFFER_BIT); // 状态使用函数

		processInput(window);
		shader.use();
		
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
```

## 纹理单元

>让我们可以使用多个纹理

使用`sampler2D`的时候，它虽然是一个uniform，但是我们却不用`glUniform`赋值。

但是我们可以给纹理采样器分配一个位置值，这样的话我们能够在一个片段着色器中设置多个纹理。一个纹理的位置通常称为一个纹理单元。

一个纹理的默认纹理单元是0，是默认的激活纹理单元，所以我们没有分配一个位置值。

通过把纹理单元赋值给采样器，我们可以一次绑定多个纹理，只要我们首先激活对应的纹理单元。就像glBindTexture一样，我们可以使用glActiveTexture激活纹理单元，传入我们需要使用的纹理单元：

```c++
glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
glBindTexture(GL_TEXTURE_2D, texture);
```

激活纹理单元之后，接下来的`glBindTexture`函数调用会绑定这个纹理到当前激活的纹理单元，纹理单元`GL_TEXTURE0`默认总是被激活，所以我们在前面的例子里当我们使用`glBindTexture`的时候，无需激活任何纹理单元。

所以我们现在可以在片段着色器中来接受另一个`sampler`。

```c++
#version 330 core

in vec3 ourColor;  // 从顶点着色器接收的颜色数据
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;  // 片段着色器的输出颜色
void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);  // 将接收到的颜色值转换为 vec4，并设置 alpha 为 1.0（不透明）
};
```

最终输出颜色现在是两个纹理的结合。GLSL内建的mix函数需要接受两个值作为参数，并对它们根据第三个参数进行线性插值。如果第三个值是`0.0`，它会返回第一个输入；如果是`1.0`，会返回第二个输入值。`0.2`会返回`80%`的第一个输入颜色和`20%`的第二个输入颜色，即返回两个纹理的混合色。

现在我们再创建另外一个纹理，这个图片包含了alpha(透明度)通道，因此要使用GL_RGBA参数：

```c++
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
    // 第一个GL_RGB参数是代表了这个图像在我们OpenGL中的内部存储格式，也就是你希望的存储格式
    // 第二个GL_RGBA是这个图像的源数据格式
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
	std::cout << "Failed to load image." << std::endl;
}
stbi_image_free(data);
```

然后指定对应的激活对应的纹理单元，让它对应到我们的两个纹理中。

```c++
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);

shader.use();
unsigned int textureUniformLocation1 = glGetUniformLocation(shader.ID, "texture1");
unsigned int textureUniformLocation2 = glGetUniformLocation(shader.ID, "texture2");
glUniform1i(textureUniformLocation1, 0);
glUniform1i(textureUniformLocation2, 1);
```

然后渲染就可以了

![image-20241204181316297](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204181316297.png)

OpenGL要求y轴0.0的坐标是在图片的底部的，但是图片的y轴0.0坐标通常在顶部，所以在图像加载的时候需要反转一下图像。

在加载图像之前加入

```c++
stbi_set_flip_vertically_on_load(true);
```

![image-20241204181421429](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241204181421429.png)

非常感谢作者的讲解！[纹理 - LearnOpenGL CN](https://learnopengl-cn.github.io/01 Getting started/06 Textures/)
