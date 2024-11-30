# How OpenGL Works？

 OpenGL允许我们实际访问CPU，是图形化编程接口Direct3D，Vulkan，Metal也是

OpenGL本身的核心只是一个规范，实际上并没有定义任何代码或者任何东西，它只是列出一个规范 ，而没有具体的实现。也就是它绝对不是一个库，也不是一个引擎和框架。实现代码的只是你们的CPU制造商虽然OpenGL是跨平台的，但是也不意味着它更好，因为通常平台原生的接口会更强大。

如果你想在多个平台上发布游戏，当然OpenGL是最简单的。

# 创建一个窗口，Start！

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

# 使用现代OpenGL

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

# 顶点缓冲区

内存缓冲区，一个内存字节数组，只是个缓冲区，它实际上在显卡上，在VRAM（显存）中

我们要定义一些数据来表示三角形，然后放进VRAM中，然后执行绘制指令

OpenGL的具体的操作其实是一个状态机，不要将其看成对象或者类似的东西，我们所做的就是设置一系列的状态。

根据你选择的一个缓冲区，然后指定着色器（告诉OpenGL这些数据如何绘制），然后让OpenGL绘制三角形。

```c++
    float positions[6] =
    {
        -0.5,0,
        0,0.5,
        0.5,0
    };
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

```

我们可以到去查看每一个函数的意思

```html
docs.gl
```

对于glGenBuffers，我们可以指定要生成多少个缓冲区，然后指定缓冲区对象名称的数组，你可以把buffer就当成当前缓冲区的一个id

![image-20241130132903565](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130132903565.png)

如果我们要使用这个缓冲区的话，我们需要绑定缓冲区的对象，也就是指定缓冲区

![image-20241130133042257](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130133042257.png)

glBufferData就是将我们的需要复制的数据传给缓冲区

`STATIC`你可以理解为，我们不会在每一帧中都修改这个数据，但是会在每一帧中都去绘制数据

`DYNAMIC`可以理解为，我们可能会频繁修改数据，然后在很多帧中去绘制数据

![image-20241130133435170](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130133435170.png)

# 顶点属性和内存布局

OpenGL管道的工作原理就是为我们的显卡提供数据，显卡上存储着一些内存，包含了我们想要绘制的所有数据

着色器，就是一个在显卡上执行的程序来读取数据，并显示在屏幕上

通常我们画几何图形的方式，就是使用一个叫做顶点缓冲区的东西，基本上是存储在显卡上的内存缓冲区

因此通常编写着色器的时候，是从读取顶点缓冲区开始的。

现在我们需要来告诉OpenGL我们缓冲区的布局：

![image-20241130143658702](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130143658702.png)

```c++
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
```

![image-20241130143844203](C:\Users\windows\AppData\Roaming\Typora\typora-user-images\image-20241130143844203.png)

**`index`**

- 指定要修改的通用顶点属性的索引。每个顶点属性都有一个唯一的索引，通常可以通过 `glGetAttribLocation` 函数从着色器程序中获取。
- 如果你在着色器中声明了一个属性 `in vec3 position;`，那么 `index` 就是该属性的索引。
- 在本例中我们只有一个位置属性，所以就是从0开始

**`size`**

- 指定每个顶点属性包含的分量数。可以是 1, 2, 3, 4。
  - 对于位置属性 `vec3 position;`，`size` 应为 3（表示三个浮动分量）。
  - 对于颜色属性 `vec4 color;`，`size` 应为 4（表示四个浮动分量）。

**`type`**

- 意义

  : 指定数组中每个组件的数据类型。常见的类型包括：

  - `GL_FLOAT`：表示浮动数据（如位置、法线、颜色等）。
  - `GL_INT`：表示整数数据（如纹理坐标）。
  - `GL_UNSIGNED_BYTE`：表示无符号字节数据。

- **例子**: 对于位置数据，通常使用 `GL_FLOAT`。

**`normalized`**

- **意义**: 如果为 `GL_TRUE`，表示将整数类型的值归一化到 [0,1] 或 [-1,1] 范围内。对于浮动数据，通常设置为 `GL_FALSE`。
- **例子**: 对于整数类型（如 `GL_BYTE` 或 `GL_UNSIGNED_BYTE`），通常使用归一化，以确保它们映射到浮动类型时保持有效范围。

**`stride`**：
假设每个顶点包含了多个属性，比如**位置、纹理坐标、法向量**等。`stride`的作用是指定从一个顶点到下一个顶点的字节偏移量。假设你的顶点数据按以下结构存储：

- 3个 `float` 用来存储位置 (每个 `float` 占4字节，共12字节)
- 2个 `float` 用来存储纹理坐标 (共8字节)
- 3个 `float` 用来存储法向量 (共12字节)

所以每个顶点的总大小是：
`12 + 8 + 12 = 32` 字节

因此，`stride` 就是 `32` 字节，表示每个顶点的起始位置与下一个顶点的起始位置之间的距离。

**`pointer`**：
`pointer` 是指数据在缓冲区中的偏移量，指示从哪里开始读取数据。假设缓冲区中的顶点数据结构如前所示，从位置开始，按顺序存储位置、纹理坐标、法向量。如果我们设置：

- `pointer = 0`，表示从第一个 `float`（位置的第一个值）开始读取。
- `pointer = 12`，表示从纹理坐标的第一个值开始读取，因为位置占了12个字节。
- `pointer = 20`，表示从法向量的第一个值开始读取，因为纹理坐标占了8个字节。

```c++
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
```

# 着色器