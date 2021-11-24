//
// Created by GuoXinYu on 2021/11/24.
//
#include <malloc.h>
#include "stdio.h"
#include "string.h"

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

// 学生管理系统的全局对象
stu_obj * g_obj;

int main() {

    printf("*****************************************\n");
    printf("欢迎使用 5907118053 郭昕宇 制作的学生管理系统!\n");
    printf("*****************************************\n");
    g_obj = create_stu_obj();
    int flag;
    while (1) {
        printf("*****************************************\n");
        printf("功能菜单\n");
        printf("*****************************************\n");
        printf("1.学生及成绩录入           2.查询功能\n");
        printf("3.信息编辑功能            4.统计功能\n");
        printf("5.退出程序\n");
        printf("******************************************\n");
        printf("请选择功能：\t\n");
        int n = scanf("%d", &flag);
        if ( n != 1) {
            //清除非法的输入 方便后面重试
            clear_stdin();
            printf("!!!输入非法，请输入数字序号!!!\n");
        }else {
            switch (flag) {
                case 1:
                    infos_create_options();
                    break;
                case 2:
                    query_options();
                    break;
                case 3:
                    edit_options();
                    break;
                case 4:
                    statistics_options();
                    break;
                case 5:
                    printf("程序即将退出~~~\n");
                    return 0;
                default:
                    printf("输入序号有误， 请重新输入\n");
            }
        }
    }
}

//
void clear_stdin() {
    //清除非法的输入 方便后面重试
    scanf("%*[^\n]%*c");
}

stu_obj *create_stu_obj() {
    // 申请学生对象所需要的堆地址
    stu_obj * obj  =(stu_obj *)malloc(sizeof(stu_obj));
    obj->head = (student_node *) malloc(sizeof(student_node));
    obj->head->next = NULL;
    obj->count = 0;
    obj->cur = obj->head;
    return  obj;
}

void infos_create_options() {
    clear_stdin();
    while (1) {
        printf("===当前为学生成绩录入===\n");
        student_node *stu = (student_node *) malloc(sizeof(student_node));
        printf("请输入学生学号 姓名 分数 （中间以一个空格分隔）\n");
        if (scanf("%s %s %d", stu->id, stu->name, &stu->score) != 3) {
            printf("格式错误 请重新输入\n");
            clear_stdin();
            // 释放删除的节点的空间
            free(stu);
        }else {
            clear_stdin();
            g_obj->cur->next = stu;
            g_obj->cur = stu;
            g_obj->count++;
            printf("%s %s %d", g_obj->cur->name, g_obj->cur->id, g_obj->cur->score);
            printf(" 已录入，是否继续？输入 1 继续，其他键返回上一级菜单\n");
            int flag;
            clear_stdin();
            scanf("%d",&flag);
            clear_stdin();
            // 如果为1继续录入 否则函数返回 结束录入
            if (flag ==1) {
                continue;
            }
            return;
        }
    }
}

void query_options() {
    while (1) {
        clear_stdin();
        printf("===当前为查询功能===\n");
        printf("1.按学号查询\t\t 2.按分数查询 \n3.显示所有学生信息\t\t 4.返回上一级菜单\n");
        int flag;
        scanf("%d", &flag);
        switch (flag) {
            case 1: {
                char input[10];
                printf("输入学号:");
                scanf("%s", input);
                clear_stdin();
                query_by_id(input);
                break;
            }
            case 2: {
                int input;
                printf("输入查询的成绩：");
                scanf("%d", &input);
                clear_stdin();
                query_by_score(input);
                break;
            }
            case 3:
                query_all();
                break;
            case 4:
                return;
            default:
                printf("输入有误 请重新输入！！\n");
        }
    }
}

// 通过学号来进行查询
void query_by_id(char input[]) {
    struct student_node *cur = g_obj->head->next;
    while (cur!= NULL) {
        if (strcmp(cur->id, input) == 0 ) {
            printf("学号：%s ，姓名：%s， 分数： %d\n", cur->id, cur->name, cur->score);
        }
        cur = cur->next;
    }
    printf("查询完毕！！");
}
// 通过分数来进行查询
void query_by_score(int input) {
    student_node *cur = g_obj->head->next;
    while (cur!= NULL) {
        if (cur->score == input) {
            printf("学号：%s ，姓名：%s， 分数： %d\n", cur->id, cur->name, cur->score);
        }
        cur = cur->next;
    }
    printf("查询完毕！！");
}

// 查询所有数据
void query_all() {
    struct student_node *cur = g_obj->head->next;
    while (cur!= NULL) {
        printf("学号：%s ，姓名：%s， 分数： %d\n", cur->id, cur->name, cur->score);
        cur = cur->next;
    }
    printf("查询完毕！！");
}

// 编辑功能的一级菜单
void edit_options() {
    while (1) {
        clear_stdin();
        printf("===当前为信息编辑功能===\n");
        printf("1.增加记录\t\t 2.删除记录 \n3.修改记录\t\t 4.返回上一级菜单\n");
        int flag;
        scanf("%d", &flag);
        switch (flag) {
            case 1: {
                add_info();
                break;
            }
            case 2: {
                del_info();
                break;
            }
            case 3:
                update_info();
                break;
            case 4:
                return;
            default:
                printf("输入有误 请重新输入！！\n");
        }
    }
}

void add_info() {
    clear_stdin();
    int flag;
    student_node *node; //作为插入节点位置的指针
    printf("选择：1.在尾部添加 \t2.在指定位置之后添加\n");
    scanf("%d", &flag);
    clear_stdin();

    // 在指定位置之后添加
    if (flag ==2) {
        printf("请输入指定学号 【程序将在该学号后面插入新数据】\n");
        char input[100];
        scanf("%s", input);
        clear_stdin();
        student_node *pos = g_obj->head->next;
        while (pos != NULL) {
            if(strcmp(input, pos->id) ==0 ) {
                break;
            }
            pos = pos->next;
        }
        //如果没有找到相应的位置 改为在末尾插入
        if (pos== NULL) {
            node = g_obj->cur;
            printf("没有找到相应的插入位置，转为默认在尾部插入\n");
        }else {
            node = pos;
        }
    }else if (flag == 1) {
        node = g_obj->cur;
    }else {
        printf("!!!输入错误，请重新输入！！！\n");
        return;
    }
    
    student_node *stu = (student_node *) malloc(sizeof(student_node));
    printf("请输入学生学号 姓名 分数 （中间以一个空格分隔）\n");
    if (scanf("%s %s %d", stu->id, stu->name, &stu->score) == 3) {
        student_node *temp = node->next;
        node->next = stu;
        stu->next = temp;

        // 判断插入的位置是不是最后一个位置 如果是的话 游标指针要向后移动
        if (node==g_obj->cur) {
            g_obj->cur = stu;
        }
    }else {
        printf("！！！输入格式有误，正在返回上级菜单！！！\n");
        free(stu);
        return;
    }
}

void del_info() {
    clear_stdin();
    int flag;
    student_node *pre, *node; //作为删除节点的前一个指针和当前指针
    printf("选择：1.按学号删除\t2.按指定成绩删除（删除第一个满足条件的学生成绩）\n");
    scanf("%d", &flag);
    clear_stdin();
    if (flag==1) {
        printf("请输入学号：");
        char input[10];
        scanf("%s", input);
        clear_stdin();
        node = g_obj->head->next;
        pre = g_obj->head;
        while(node != NULL) {
            if (strcmp(node->id, input) == 0) {
                break;
            }else {
                node = node->next;
                pre = pre->next;
            }
        }
        if (node == NULL) {
            printf("未匹配到相关数据\n");
            return;
        }
    }else if (flag==2) {
        //按成绩删除
        printf("请输入成绩：");
        int input = 0;
        scanf("%d", &input);
        clear_stdin();
        node = g_obj->head->next;
        pre = g_obj->head;
        while(node != NULL) {
            if (node->score == input) {
                break;
            }else {
                node = node->next;
                pre = pre->next;
            }
        }
        if (node == NULL) {
            printf("未匹配到相关数据");
            return;
        }
    }else {
        printf("输入有误 请重试");
    }
    pre->next = node->next;
    printf("删除的数据为：学号 %s， 姓名 %s, 成绩 %d", node->id, node->name, node->score);
    free(node);
}

void update_info() {
    clear_stdin();
    char input[100];
    printf("输入要更改的学号：");
    scanf("%s", input);
    clear_stdin();
    char name[20];
    char id[10];
    int score;
    printf("请按照 学号 姓名 分数 重新输入需要更改的信息:\n");
    if (scanf("%s %s %d", id, name, &score)!=3) {
        printf("输入不合法 正在返回上一级菜单\n");
        clear_stdin();
        return;
    }
    student_node *node =g_obj->head->next;
    while(node != NULL) {
        if (strcmp(input, node->id)==0) {
            break;
        }
        node = node->next;
    }
    if (node != NULL) {
        strcpy(node->id, id);
        strcpy(node->name, name);
        node->score = score;
    }
    printf("修改完毕\n");
}

void statistics_options() {
    int count = 0;
    float avg = 0;
    int n = 0;
    student_node *max_score_stu;
    student_node *min_score_stu;
    student_node *cur = g_obj->head->next;
    // 遍历一遍 计算出总分数和总共的学生个数
    while (cur != NULL) {
        count += cur->score;
        n++;
        if (max_score_stu ==NULL || max_score_stu->score < cur->score) {
            max_score_stu = cur;
        }
        if (min_score_stu == NULL || min_score_stu->score > cur->score) {
            min_score_stu = cur;
        }
        cur = cur->next;
    }
    if (n!=0) {
        avg = (float)(count)/(float)n;
    }
    // 下面实现排序输出
    student_node *sortedFirst = sortList(g_obj->head->next);
    student_node *sort_cur = sortedFirst;
    while (sort_cur != NULL) {
        printf("学号 %s 姓名 %s  分数%d\n", sort_cur->id, sort_cur->name , sort_cur->score);
        sort_cur = sort_cur->next;
    }
    printf("总计：%d 分      平均：%f分\n",count, avg);
    if (n!= 0) {
        printf("最高分 学号 %s 姓名 %s 分数 %d\n", max_score_stu->id, max_score_stu->name, max_score_stu->score);
        printf("最低分 学号 %s 姓名 %s 分数 %d\n", min_score_stu->id, min_score_stu->name, min_score_stu->score);
    }
}



// 归并排序的 merge 操作 原理是把两个有序的链表 合并成一个大的有序的链表
struct student_node * merge(struct student_node * head1, struct student_node * head2) {
    // 建立遍历的游标
    struct student_node * dummyHead = malloc(sizeof(struct student_node));
    dummyHead->score = 0;
    struct student_node *temp = dummyHead, *temp1 = head1, *temp2 = head2;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->score <= temp2->score) {
            temp->next = temp1;
            temp1 = temp1->next;
        } else {
            temp->next = temp2;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    if (temp1 != NULL) {
        temp->next = temp1;
    } else if (temp2 != NULL) {
        temp->next = temp2;
    }
    return dummyHead->next;
}

// 排序函数
student_node * toSortList(struct student_node * head, struct student_node * tail) {
    if (head == NULL) {
        return head;
    }
    if (head->next == tail) {
        head->next = NULL;
        return head;
    }
    struct student_node *slow = head, *fast = head;
    while (fast != tail) {
        slow = slow->next;
        fast = fast->next;
        if (fast != tail) {
            fast = fast->next;
        }
    }
    struct student_node* mid = slow;
    return merge(toSortList(head, mid), toSortList(mid, tail));
}

struct student_node * sortList(struct student_node * head) {
    return toSortList(head, NULL);
}






