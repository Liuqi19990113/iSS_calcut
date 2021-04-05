
Version 1 date 3.19
#make
    1.在playground下解压文件夹
    2.在文件夹中mkdir build
    3.cd build
    4.cmake .. 
    5.make 此时会在文件夹中建立sample_cut.exe，编译完成。

#头文件以及源文件介绍
    1.urqmd_read.h  &  urqmd_read.cpp
        在头文件中声明了urqmd_qgp_function这个函数并且在源文件中给出相应的定义，该函数的输入是string生成的urqmd_result19路径的对象，输出是一个指向数组的指针，数组的第一项是qgp总能量，第二项是qgp_pz方向的总动量。

    
    2.line.h  &  line.cpp
        在头文件中定义了两个类：particle_line以及title_line。顾名思义，这两个类是用来处理文件的行信息的。
        particle_line的数据成员是energy，pz和y。其分别对应粒子的能量动量和快度。在生成一个新的对象后，通过内部的particle_information(string line)方法对这个对象的数据成员进行赋值，该方法的定义在相应的源文件中。      //这里的 string line是OSCAR.DAT文件中表示粒子的一行
        title_line的数据成员是sample_order，particle_numer。其分别对应这是第几次sample和这次sample产生的粒子数目。在生成一个新的对象后，通过内部的title_information(string line)方法对这个对象的数据成员进行赋值，该方法的定义在相应的源文件中。      ////这里的 string line是OSCAR.DAT文件中每次sample开始的一行

    3.cal_ycut.h  &  cal_ycut.cpp
        在头文件中声明了三个函数：分别是cal_ycut(), sample_by_sample_cal(), all_sample_cal()。sample_by_sample_cal()和all_sample_cal()分别是对单个sample结果进行ycut计算，在控制台输出所有sample结果的ycut和对所有的sample结果统一计算出一个ycut并在控制台输出。这两个函数的输入分别是一些参数以及OSCAR.DAT文件，其在函数内部生成一个energy_list和pz_list储存不同格点的能量值和动量值，然后在这两个函数中调用cal_ycut()进行计算。
        cal_ycut()的输入是一些参数的上述的energy_list和pz_list,通过遍历所有的格点去计算y_cut。

    4.main.cpp
        这个源文件主要是不同的参数和调用。
        y_step:格点大小
        y_left:iSS参数卡中的y_lb
        y_right:iSS参数卡中的y_rb
        能动量的百分差允许值在cal_ycut函数中调节



Version 2 date 3.22
#更改与新增
    1.在particle_line中新增数据成员，用于表示粒子的横向动量和赝快度。在相应的成员函数中加入了获取相应值的模块。
    2.新增para_read.h  &  para_read.cpp文件，在其中定义了一个类用于储存参数卡的参数。
    3.新增cal_etacut.h  &  cal_etacut.cpp文件，其结构于cal_ycut相似，用于计算eta_cut。
    4.新增parameter.txt参数卡，具体说明见参数卡注释，要注意的是由于总有大的赝快度粒子出现，所以eta_left和eta_right要设置的大一些以免出现溢出错误。
    5.读取文件时使用了相对路径，现在不需要手动调节路径。



Version 3 date 3.24
#更改与新增
    1.在cal_etacut.h  &  cal_etacut.cpp中增加了新的函数cal_etacut_with_ouput,用于输出每一个sample结果的etacut，输出内容储存在目录的eta cut result of each sample.txt 下。
    2.新增output.h  &  output.cpp，用于输出每个sample处于eta cut范围内粒子的OSCAR1997文件，输出内容储存在目录的iSS result after cut.txt下。
    3.解决了accpet error固定为0.01的bug。
    4.上传到了github中，项目地址为https://github.com/Liuqi19990113/iSS_calcut
    
    
    
Version 4 date 3.30
#更改与新增
    1.更改了output.cpp的输出格式来适配osc2u程序，相应的在output.h中新增了头文件<string.h>
    


Version 5 date 3.30
#更改与新增
    1.新增了cal_particle_by_particle.h  &  cal_pbyp.cpp来particle by particle的计算eta_cut，其option在参数卡中设置
    
    

Version 6 date 4.5
#更改与新增
    1.在eta_cut的lattice计算方法中剔除了超出参数卡中eta的粒子，并在控制台中输出剔除的粒子数。
    2.改变了输出文件的结构，现在输出文件只有两个，一个是每个sample结果的eta_cut,另一个是最终的OSCAR文件，都储存在results_of_cal文件夹中。
    3.为eta_cut的particle by particle 方法添加了输出
