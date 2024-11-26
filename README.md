# ThreadHandleObject
Unreal Engine 5.3 plugin to create and handle threads.

Thread Handle Object Technical Documentation 

THREAD HANDLE OBJECT

TECHNICAL DOCUMENTATION

TABLE OF CONTENTS

[Introduction](#_page2_x70.00_y72.00)
[Target Audience](#_page2_x70.00_y216.00)
[Product Objectives](#_page2_x70.00_y317.00)
[Design Goals](#_page2_x70.00_y432.00)
[Design Flow](#_page3_x70.00_y72.00)
[Logical Behaviour](#_page4_x70.00_y72.00)
[Process View](#_page5_x70.00_y72.00)
[Use Case View](#_page6_x70.00_y72.00)

1. **<a name="_page2_x70.00_y72.00"></a>Introduction** 

During the development of my capstone team project in the third year of the Game Development program at Algonquin College, I developed a **UObject** wrapper for spawning and managing threads in Unreal Engine C++. The **ThreadHandleObject** is a simple UObject subclass that can be initialized like a normal ActorComponent or Actor inside any UCLASS. This document provides an architectural overview of the system and also functions as a foundational reference point for the developers. 

2. **Target<a name="_page2_x70.00_y216.00"></a> Audience** 

This document is intended for technical stakeholders, particularly the development team, and assumes that the reader has a basic technical background in Unreal Engine C++. 

3. **Product<a name="_page2_x70.00_y317.00"></a> Objectives** 

The **ThreadHandleObject** aims to provide a user-friendly wrapper for FRunnable threading framework inside Unreal Engine, keeping raw C++ code separate from Unreal C++ framework, customizable threading framework, and stable code execution using mutex locking. 

4. **Design<a name="_page2_x70.00_y432.00"></a> Goals** 

The design goals for creating the **ThreadHandleObject** are: 

- Easy to initialize and create threads and stay inside the Unreal Engine Framework. 
- Provide thread looping functionality such as **is Tick enabled**, and **start on initialize**. 
- Wrap around the raw C++ code in the FRunnable class. 
- Provide functions for mutex locking and unlocking. 
5. **Design<a name="_page3_x70.00_y72.00"></a> Flow** 

The basic ThreadHandleObject execution consists of 4 steps: 

  **Initialization** 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.001.png)

  **Binding the Run Thread Body** 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.002.png)

  **Starting the Thread** 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.003.png)

  **Running the Thread** 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.004.png)

6. **Logical<a name="_page4_x70.00_y72.00"></a> Behaviour** 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.005.png)

The main class, **UThreadHandleObject** is an Object of the Unreal Engine framework. It consists of one FThreadBase pointer, initialized in the Initialize() function. The FThreadBase is a subclass of FRunnable, overriding some basic functions, including Init, Run, and Stop. 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.006.png)

7. **Process<a name="_page5_x70.00_y72.00"></a> View** 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.007.png)

8. **Use<a name="_page6_x70.00_y72.00"></a> Case View** 

The first step is to create the ThreadHandleObject. Like any UObject, it is created in the constructor of an owning UObject: 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.008.png)

Before spawning a thread, the ThreadHandleObject must be initialized. The initialization can be done from any function: 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.009.png)

The first argument in the Initialize() function is to set IsTickEnabled. The second argument is for whether to auto start the thread or not. 

**Note:** The auto-start option will not do anything until a function is bound to the **RunDelegate**. 

The ThreadHandleObject requires a function bound to its RunDelegate to utilize the multi-threading functionality. 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.010.png)

If auto start is enabled, the ThreadHandleObject will start executing the bound function. To start the threading process, simply call the StartThread() function. 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.011.png)

You can utilize the mutex locking and unlocking like so: 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.012.png)

And…. 

![](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.013.png)
[](readme_images/Aspose.Words.21330127-f8ef-4695-b1b3-0306705b814f.014.png)
