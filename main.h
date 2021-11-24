//
// Created by guo on 2021/11/24.
//

#ifndef C_INNOVATION_LABS_MAIN_H
#define C_INNOVATION_LABS_MAIN_H

#endif //C_INNOVATION_LABS_MAIN_H


typedef struct student_node {
    char  name[20];               //学生名字 预备20个长度 防止各种奇奇怪怪的名字
    char  id[10];                 // 学生学号 10位学号如 59071100001
    int   score;                  // 同学的分数
    struct student_node *next;    // 指向下一个学生节点
} student_node;


typedef struct students_object {
    int count;             // 当前存在的学生人数
    student_node  *head;   // 用来做学生node 的头结点不存储对象
    student_node  *cur;    // cur 作为游标 总是指向链表中最后一个节点， 方便插入新的节点
} stu_obj;


void infos_create_options();  // 1.学生及成绩信息的录入 一级功能菜单


void query_options();               // 2.  查询功能一级菜单
void query_by_id(char input[]);     // 2.1 按学号查询
void query_by_score();              // 2.2 按分数查询
void query_all();                   // 2.3 查询所有

void edit_options();                // 3. 信息的编辑功能一级菜单
void add_info();                    // 3.1 增加记录
void del_info();                    // 3.2 删除记录
void update_info();                 // 3.3 修改记录


void statistics_options();


// 用来清空非法输入流
void clear_stdin();
// 用来创建学习系统的顶级持有对象 返回 stu_obj 结构
stu_obj *create_stu_obj();

// 使用自顶向下归并排序来优化排序所有的成绩
// 时间复杂度 O(nlogn)
student_node * sortList(struct student_node * head);
