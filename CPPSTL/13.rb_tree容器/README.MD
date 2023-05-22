# 容器 rb_tree

Red-Black tree(红黑树)是平衡二叉搜索树(balanced binary search tree)中常被使用的一种。平衡二叉搜索树的特征：排列规则有search和insert，并保持适度平衡——无任何节点过深。

re_tree提供“遍历”操作及iterators。
按正常规则(++iterators)遍历，便能获得排序状态(sorted)。

我们***不应***使用re_tree的iterators改变元素值(因为元素有其严谨排列规则)。变成层面***并未阻绝此事***。如设计是正确的，因为rb_tree即将为set和map服务(作为其底部支持)，而map允许元素的data改变，只有元素的key才是不可被改变的。

re_tree提供两种insertion操作：**insert_unique()**和**insert_equal()**。
前者表示节点的key一定在整个tree中独一无二，否则安插失败。
后者表示节点的key可重复。

<font color=red>我是红色</font>