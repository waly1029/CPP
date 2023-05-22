// #include <iostream>


// #################################################################
// #                                                               #
// #                                                               #
// #              所有algorithm，其内最终设计元素本身的操作              #
// #                         无非就是比大小                           #
// #                                                               #
// #                                                               #
// #################################################################



// OOP试图将data和methods关联在一起

// OOP的情况
// template<class T, class Alloc=alloc>
// class list{
// // ...

//     // OOP的情况应该是数据和算法在一个类中
//     void sort();
// };

// =================================================================
// GP是将data和methods分开来
// Containers和Algorithms团队可以分开分别各自工作
// 之后利用iterator来进行data和algorithms之间的沟通

// Data Structures

// template<class T, class Alloc=alloc>
// class vector{
//     // ...

//     // 无sort
// };

// Algorithms

// template<...>
// inline sort(...) {
// ....
// }

