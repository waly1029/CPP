![algorithm](./images/%20whatisalgorithm.jpg)


## 各种容器的iterators的iterator_category
```c++
// 五种iterator category
struct input_iterator_tag {};
struct ouput_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};
```
