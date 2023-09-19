//
// Created by User on 2023/9/18.
//
/**
 * 可通过这个例子试用
 */
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <sys/stat.h>	// 获取文件大小

#include "cJSON.h"


#define FILE_NAME "text.json"


// 封装Json
void createJson ();
// 解析Json
void parseJson();
// 修改Json
void alterJson();
// 删除Json
void delJson();

int main (void) {

    createJson();

    parseJson();

    alterJson();

    delJson();

    return 0;
}


void createJson () {

    /*
        "interest": {
            "basketball": "篮球",
            "badminton": "羽毛球"
        },
    */
    // 定义对象 { }
    cJSON *interest = cJSON_CreateObject();
    // 插入元素，对应 键值对
    cJSON_AddItemToObject(interest, "basketball", cJSON_CreateString("篮球"));		// 当值是字符串时，需要使用函数cJSON_CreateString()创建
    cJSON_AddItemToObject(interest, "badminton", cJSON_CreateString("羽毛球"));
    //cJSON_AddStringToObject(interest, "badminton", "羽毛球");	// 或者这样写


    /*
        "color": [ "black", "white" ],
    */
    // 定义 [ ] 数组
    cJSON *color = cJSON_CreateArray();
    // 往数组中添加元素
    cJSON_AddItemToArray(color, cJSON_CreateString("black"));
    cJSON_AddItemToArray(color, cJSON_CreateString("white"));



    /*
        "like": [
            { "game": "马里奥", "price": 66.6 },
            { "game": "魂斗罗", "price": 77.7 }
        ],
    */
    // 定义 { } 对象
    cJSON *likeObject1 = cJSON_CreateObject();
    cJSON_AddItemToObject(likeObject1, "game", cJSON_CreateString("马里奥"));
    cJSON_AddItemToObject(likeObject1, "price", cJSON_CreateNumber(66.6));		// 当值是数字时，需要使用函数cJSON_CreateNumber()创建
    //cJSON_AddNumberToObject(likeObject1, "price", 66.6);	// 或者这样写

    cJSON *likeObject2 = cJSON_CreateObject();
    cJSON_AddItemToObject(likeObject2, "game", cJSON_CreateString("魂斗罗"));
    cJSON_AddItemToObject(likeObject2, "price", cJSON_CreateNumber(77.7));

    // 定义 [ ] 数组
    cJSON *like = cJSON_CreateArray();
    // 往数组中添加元素
    cJSON_AddItemToArray(like, likeObject1);
    cJSON_AddItemToArray(like, likeObject2);



    /*
        "education": [
            [ "小学", "初中" ],
            [ "高中", "大学" ]
        ],
    */
    // 定义 [ ] 数组
    cJSON *education1 = cJSON_CreateArray();
    cJSON_AddItemToArray(education1, cJSON_CreateString("小学"));
    cJSON_AddItemToArray(education1, cJSON_CreateString("初中"));

    cJSON *education2 = cJSON_CreateArray();
    cJSON_AddItemToArray(education2, cJSON_CreateString("高中"));
    cJSON_AddItemToArray(education2, cJSON_CreateString("大学"));

    // 定义 [ ] 数组
    cJSON *education = cJSON_CreateArray();
    cJSON_AddItemToArray(education, education1);
    cJSON_AddItemToArray(education, education2);



    /*
        "languages": {
            "serialOne": { "language": "汉语", "grade": 10 },
            "serialTwo": { "language": "英语", "grade": 6}
        },
    */
    // 定义对象 { }
    cJSON *serialOne = cJSON_CreateObject();
    cJSON_AddItemToObject(serialOne, "language", cJSON_CreateString("汉语"));
    cJSON_AddItemToObject(serialOne, "grade", cJSON_CreateNumber(10));

    cJSON *serialTwo = cJSON_CreateObject();
    cJSON_AddItemToObject(serialTwo, "language", cJSON_CreateString("英语"));
    cJSON_AddItemToObject(serialTwo, "grade", cJSON_CreateNumber(6));

    // 定义对象 { }
    cJSON *languages = cJSON_CreateObject();
    cJSON_AddItemToObject(languages, "serialOne", serialOne);
    cJSON_AddItemToObject(languages, "serialTwo", serialTwo);






    // 创建跟对象
    cJSON *root = cJSON_CreateObject();

    // 将子项插入根项中
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("小明"));	// "name":	"小明"
    cJSON_AddItemToObject(root, "age", cJSON_CreateNumber(23));			// "age":	23
    cJSON_AddItemToObject(root, "interest", interest);
    cJSON_AddItemToObject(root, "color", color);
    cJSON_AddItemToObject(root, "like", like);
    cJSON_AddItemToObject(root, "education", education);
    cJSON_AddItemToObject(root, "languages", languages);
    cJSON_AddItemToObject(root, "vip", cJSON_CreateTrue());	// "vip":	true		插入布尔类型数据需要使用cJSON_CreateBool函数
    cJSON_AddItemToObject(root, "address", cJSON_CreateNull());	// "address":	null	插入NULL值需要使用cJSON_CreateNull函数
    //cJSON_AddTrueToObject(root, "vip");
    //cJSON_AddNullToObject(root, "address");	// 或者这样写也是可以的

    // 打印控制台查看
    char *cPrint = cJSON_Print(root);
    char *cPrintUnformatted = cJSON_PrintUnformatted(root);
    printf("cJSON_Print：\n%s\n\n\n", cPrint);		// cJSON_Print：有做格式调整
    printf("cJSON_PrintUnformatted：\n%s\n\n\n", cPrintUnformatted);	// cJSON_PrintUnformatted：没有做格式调整
    // 返回的字符串指针需要自己释放
    free(cPrint);
    free(cPrintUnformatted);



    // 打开文件
    FILE *file = NULL;
    file = fopen(FILE_NAME, "w");	// FILE_NAME ==> "jss.json"
    if (file == NULL) {
        printf("Open file fail！\n");

        // 释放指针内存
        cJSON_Delete(root);
        return;
    }

    char *cjValue = cJSON_Print(root);
    // 写入文件
    //int ret = fwrite(cjValue, sizeof(char), strlen(cjValue), file);
    int ret = fputs(cjValue, file);
    if (ret == EOF) {
        printf("写入文件失败！\n");
    }

    fclose(file);
    free(cjValue);

    // 释放指针内存
    cJSON_Delete(root);
}

void parseJson () {

    // 打开文件
    FILE *file = NULL;
    file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Open file fail！\n");
        return;
    }


    // 获得文件大小
    struct stat statbuf;
    stat(FILE_NAME, &statbuf);
    int fileSize = statbuf.st_size;
    printf("文件大小：%d\n", fileSize);


    // 分配符合文件大小的内存
    char *jsonStr = (char *)malloc(sizeof(char) * fileSize + 1);
    memset(jsonStr, 0, fileSize + 1);


    // 读取文件中的json字符串
    int size = fread(jsonStr, sizeof(char), fileSize, file);
    if (size == 0) {
        printf("读取文件失败！\n");
        fclose(file);
        return;
    }
    printf("%s\n", jsonStr);
    fclose(file);


    // 将读取到的json字符串转换成json变量指针
    cJSON *root = cJSON_Parse(jsonStr);
    if (!root) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        free(jsonStr);
        return;
    }
    free(jsonStr);


    cJSON *item = NULL;
    char *v_str = NULL;
    double v_double = 0.0;
    int v_int = 0;
    bool v_bool = false;


    // 解析："name":	"小明",
    item = cJSON_GetObjectItem(root, "name");
    if (item != NULL) {
        /* 写法一：*/
        // 判断是不是字符串类型
        //if (item->type == cJSON_String) {
        //	v_str = cJSON_Print(item);		// 通过函数获取值
        //	printf("name = %s\n", v_str);
        //	free(v_str);					// 通过函数返回的指针需要自行free，否则会导致内存泄漏
        //	v_str = NULL;
        //}


        /* 写法二： */
        // 判断是不是字符串类型
        if (item->type == cJSON_String) {
            v_str = item->valuestring;		// 此赋值是浅拷贝，不需要现在释放内存
            printf("name = %s\n", v_str);
        }

    }



    // 解析："age":	"23",
    item = cJSON_GetObjectItem(root, "age");
    if (item != NULL) {	// 合法性检查
        if (item->type == cJSON_Number) {		// 判断是不是数字
            v_int = item->valueint;			// 获取值
            printf("age = %d\n", v_int);
        }
    }



    // 解析："vip":	true,
    item = cJSON_GetObjectItem(root, "vip");
    if (item != NULL) {
        if (item->type == cJSON_True || item->type == cJSON_False) {
            v_str = cJSON_Print(item);		// 由于bool类型结构体中没有给出，所以使用字符串代替
            printf("vip = %s\n", v_str);
            free(v_str);
            v_str = NULL;
        }
    }



    // 解析："address":	null
    item = cJSON_GetObjectItem(root, "address");
    if (item != NULL && item->type == cJSON_NULL) {
        v_str = cJSON_Print(item);		// 由于NULL类型结构体中没有给出，所以使用字符串代替
        printf("address = %s\n", v_str);
        free(v_str);
        v_str = NULL;
    }



    /* 解析：
        "interest":	{
            "basketball":	"篮球",
            "badminton":	"羽毛球"
        },
    */
    {
        /*************** 方式一 ***************/
        item = cJSON_GetObjectItem(root, "interest");		// 获取object对象名
        if (item != NULL) {
            cJSON *val = NULL;

            val = cJSON_GetObjectItem(item, "basketball");	// 根据object对象名获得里面的basketball数据
            if (val != NULL && val->type == cJSON_String) {
                v_str = val->valuestring;
                printf("basketball = %s\n", v_str);
            }

            val = cJSON_GetObjectItem(item, "badminton");	// 根据object对象名获得里面的badminton数据
            if (val != NULL && val->type == cJSON_String) {
                v_str = val->valuestring;
                printf("badminton = %s\n", v_str);
            }
        }

        /*************** 方式二 ***************/
        item = cJSON_GetObjectItem(root, "interest");
        if (item != NULL) {
            cJSON *obj = item->child;	// 获得 "basketball":	"篮球"

            while (obj) {
                if (obj->type == cJSON_String) {
                    char *v_str = obj->valuestring;
                    printf("%s = %s\n", obj->string, v_str);	// 可以通过string获得键
                }
                // 获取下一个元素
                obj = obj->next;
            }
        }
    }




    /*	解析：
        "color":	["black", "white"],
    */
    {
        /*************** 方式一 ***************/
        item = cJSON_GetObjectItem(root, "color");
        if (item != NULL) {
            int size = cJSON_GetArraySize(item);	// 获得数组个数

            for (int i = 0; i < size; i++) {
                cJSON *arr = cJSON_GetArrayItem(item, i);	// 根据索引获得数组中的值

                if (arr != NULL && arr->type == cJSON_String) {
                    v_str = arr->valuestring;
                    printf("color = %s\n", v_str);
                }
            }
        }


        /*************** 方式二 ***************/
        item = cJSON_GetObjectItem(root, "color");
        if (item != NULL) {
            cJSON *arr = item->child;	// 获得 "black"

            while (arr) {
                if (arr->type == cJSON_String) {
                    char *v_str = arr->valuestring;
                    printf("color = %s\n", v_str);
                }
                // 获取下一个元素
                arr = arr->next;
            }
        }
    }




    /*
        "like": [
            { "game": "马里奥", "price": 66.6 },
            { "game": "魂斗罗", "price": 77.7 }
        ],
    */
    {
        /*************** 方式一 ***************/
        item = cJSON_GetObjectItem(root, "like");
        if (item != NULL) {
            int size = cJSON_GetArraySize(item);	// 获取的数组大小

            for (int i = 0; i < size; i++) {
                cJSON *obj = cJSON_GetArrayItem(item, i);		// 获取的数组里的obj
                cJSON *val = NULL;

                if (obj != NULL && obj->type == cJSON_Object) {	// 判断数字内的元素是不是obj类型
                    val = cJSON_GetObjectItem(obj, "game");		// 获得obj里的值

                    if (val != NULL && val->type == cJSON_String) {
                        v_str = val->valuestring;
                        printf("game = %s\n", v_str);
                    }

                    val = cJSON_GetObjectItem(obj, "price");
                    if (val != NULL && val->type == cJSON_Number) {
                        v_double = val->valuedouble;
                        printf("price = %.2f\n", v_double);
                    }
                }
            }
        }


        /*************** 方式二 ***************/
        item = cJSON_GetObjectItem(root, "like");
        if (item != NULL) {
            cJSON *obj = item->child;	// 获得 { "game": "马里奥", "price": 66.6 }

            while (obj) {
                if (obj->type == cJSON_Object) {

                    cJSON *objValue = obj->child;	// 获得 "game": "马里奥"
                    while (objValue) {

                        // 再通过类型去区分
                        if (objValue->type == cJSON_String) {
                            char *v_str = objValue->valuestring;
                            printf("%s = %s\n", objValue->string, v_str);

                        } else if (objValue->type == cJSON_Number) {
                            double v_double = objValue->valuedouble;
                            printf("%s = %.2f\n", objValue->string, v_double);
                        }
                        // 获取下一个元素
                        objValue = objValue->next;
                    }
                }
                // 获取下一组元素
                obj = obj->next;
            }
        }
    }




    /*
        "education": [
            [ "小学", "初中" ],
            [ "高中", "大学" ]
        ],
    */
    {
        /*************** 方式一 ***************/
        item = cJSON_GetObjectItem(root, "education");
        if (item != NULL) {
            int size = cJSON_GetArraySize(item);	// 获取的数组大小

            for (int i = 0; i < size; i++) {
                cJSON *arr = cJSON_GetArrayItem(item, i);		// 解析获得	[ "小学", "初中" ]

                if (arr != NULL && arr->type == cJSON_Array) {
                    int arrSize = cJSON_GetArraySize(arr);

                    for (int j = 0; j < arrSize; j++) {
                        cJSON *arr2 = cJSON_GetArrayItem(arr, j);	// 再进一步解析就可以得到数组里面的元素了

                        if (arr2 != NULL && arr2->type == cJSON_String) {
                            v_str = arr2->valuestring;
                            printf("education = %s\n", v_str);
                        }
                    }
                }
            }
        }

        /*************** 方式二 ***************/
        item = cJSON_GetObjectItem(root, "education");
        if (item != NULL) {
            cJSON *arr = item->child;	// 获得 [ "小学", "初中" ]

            while (arr) {
                if (arr->type == cJSON_Array) {
                    cJSON *arrValue = arr->child;	// 获得 "小学"
                    while (arrValue) {
                        if (arrValue->type == cJSON_String) {
                            char *v_str = arrValue->valuestring;
                            printf("education = %s\n", v_str);
                        }
                        arrValue = arrValue->next;	// 获取下一个元素
                    }
                }
                // 获取下一组
                arr = arr->next;
            }
        }
    }




    /*
        "languages": {
            "serialOne": { "language": "汉语", "grade": 10 },
            "serialTwo": { "language": "英语", "grade": 6}
        },
    */
    {
        /*************** 方式一 ***************/
        const char *arrStr[] = { "serialOne", "serialTwo" };		// 可以提前定义需要解析的对象键，这样就可以使用for循环进行解析了

        item = cJSON_GetObjectItem(root, "languages");
        if (item != NULL) {
            cJSON *val = NULL;
            int size = sizeof(arrStr) / sizeof(char *);

            // 通过遍历指针数组，获得每个对象的键，在进行解析操作（如果不使用for循环解析，那就老老实实的写代码将全部个数解析完毕）
            for (int i = 0; i < size; i++) {
                cJSON *obj1 = cJSON_GetObjectItem(item, arrStr[i]);

                if (obj1 != NULL && obj1->type == cJSON_Object) {

                    val = cJSON_GetObjectItem(obj1, "language");
                    if (val != NULL && val->type == cJSON_String) {
                        v_str = val->valuestring;
                        printf("education = %s\n", v_str);
                    }

                    val = cJSON_GetObjectItem(obj1, "grade");
                    if (val != NULL && val->type == cJSON_Number) {
                        v_int = val->valueint;
                        printf("grade = %d\n", v_int);
                    }
                }
            }
        }



        /*************** 方式二 ***************/
        // 在不知道键是什么的情况下 和 不知道有多少元素的情况下可用
        item = cJSON_GetObjectItem(root, "languages");
        if (item != NULL) {
            // 获取到languages里的第一个子元素
            cJSON *obj = item->child;	// 也就是："serialOne": { "language": "汉语", "grade": 10 }

            while (obj) {
                if (obj->type == cJSON_Object) {

                    // 获取到子元素的子元素
                    cJSON *value = obj->child;	// 也就是：{ "language": "汉语", "grade": 10 }

                    while (value) {
                        if (value->type == cJSON_String) {
                            printf("%s = %s\n", value->string, value->valuestring);

                        } else if (value->type == cJSON_Number) {
                            printf("%s = %d\n", value->string, value->valueint);
                        }
                        // 通过next可以自由获取里面的元素了
                        value = value->next;
                    }
                }

                // 获得下一组子元素
                obj = obj->next;
            }
        }
    }




    // 使用了cJSON_Parse之后，记得调用cJSON_Delete函数释放
    cJSON_Delete(root);
}



void alterJson() {

    // 打开文件
    FILE *file = NULL;
    file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Open file fail！\n");
        return;
    }


    // 获得文件大小
    struct stat statbuf;
    stat(FILE_NAME, &statbuf);
    int fileSize = statbuf.st_size;
    printf("文件大小：%d\n", fileSize);


    // 分配符合文件大小的内存
    char *jsonStr = (char *)malloc(sizeof(char) * fileSize + 1);
    memset(jsonStr, 0, fileSize + 1);


    // 读取文件中的json字符串
    int size = fread(jsonStr, sizeof(char), fileSize, file);
    if (size == 0) {
        printf("读取文件失败！\n");
        fclose(file);
        return;
    }
    printf("%s\n", jsonStr);
    fclose(file);


    // 将读取到的json字符串转换成json变量指针
    cJSON *root = cJSON_Parse(jsonStr);
    if (!root) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        free(jsonStr);
        return;
    }
    free(jsonStr);



    cJSON *item = NULL;


    /* "name":	"小明"		====>	"name":	"小红" */
    // 使用cJSON_ReplaceItemInObject可以直接进行修改
    cJSON_ReplaceItemInObject(root, "name", cJSON_CreateString("小红"));
    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "name");
    if (item != NULL) {
        // 判断是不是字符串类型
        if (item->type == cJSON_String) {
            char *v_str = item->valuestring;		// 此赋值是浅拷贝，不需要现在释放内存
            printf("name = %s\n", v_str);
        }
    }


    /* "age": 23		====>	"age": 20 */
    cJSON_ReplaceItemInObject(root, "age", cJSON_CreateNumber(20));
    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "age");
    if (item != NULL) {
        // 判断是不是字符串类型
        if (item->type == cJSON_Number) {
            int v_int = item->valueint;
            printf("age = %d\n", v_int);
        }
    }


    /* "vip": true	 ====>  "vip": false */
    // 使用cJSON_ReplaceItemInObject可以直接进行修改
    cJSON_ReplaceItemInObject(root, "vip", cJSON_CreateBool(false));
    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "vip");
    if (item != NULL) {
        // 判断是不是字符串类型
        if (item->type == cJSON_False || item->type == cJSON_True) {
            char *v_str = cJSON_Print(item);		// 由于bool类型结构体中没有给出，所以使用字符串代替
            printf("vip = %s\n", v_str);
            free(v_str);
            v_str = NULL;
        }
    }


    /*
        "interest":	{						 修改后：     "interest":	{
            "basketball":	"篮球",  		  ====>				"basketball":	"姚明",
            "badminton":	"羽毛球"							"badminton":	"林丹"
        }												  }
    */
    // 首先获取到需要修改的指针
    item = cJSON_GetObjectItem(root, "interest");
    if (item != NULL) {
        // 使用cJSON_ReplaceItemInObject可以直接进行修改
        cJSON_ReplaceItemInObject(item, "basketball", cJSON_CreateString("姚明"));
        cJSON_ReplaceItemInObject(item, "badminton", cJSON_CreateString("林丹"));
    }

    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "interest");
    if (item != NULL) {
        cJSON *obj = item->child;	// 获得 "basketball":	"篮球"

        while (obj) {
            if (obj->type == cJSON_String) {
                char *v_str = obj->valuestring;
                printf("%s = %s\n", obj->string, v_str);	// 可以通过string获得键
            }
            // 获取下一个元素
            obj = obj->next;
        }
    }



    /* "color":	["black", "white"]		====>		"color":["red", "blue"]	*/
    item = cJSON_GetObjectItem(root, "color");
    if (item != NULL) {
        cJSON_ReplaceItemInArray(item, 0, cJSON_CreateString("red"));
        cJSON_ReplaceItemInArray(item, 1, cJSON_CreateString("blue"));
    }

    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "color");
    if (item != NULL) {
        cJSON *arr = item->child;	// 获得 "black"

        while (arr) {
            if (arr->type == cJSON_String) {
                char *v_str = arr->valuestring;
                printf("color = %s\n", v_str);
            }
            // 获取下一个元素
            arr = arr->next;
        }
    }



    /*
        "like": [									 修改后：  "like": [
            { "game": "马里奥", "price": 66.6 },	  ====>	   		{ "game": "炸弹人", "price": 88.8 },
            { "game": "魂斗罗", "price": 77.7 }						{ "game": "中国象棋", "price": 99.9 }
        ],													   ],
    */
    item = cJSON_GetObjectItem(root, "like");
    if (item != NULL) {
        cJSON *arrObj = NULL;

        arrObj = cJSON_GetArrayItem(item, 0);	// 根据索引获得数组中的值
        cJSON_ReplaceItemInObject(arrObj, "game", cJSON_CreateString("炸弹人"));
        cJSON_ReplaceItemInObject(arrObj, "price", cJSON_CreateNumber(88.8));

        arrObj = cJSON_GetArrayItem(item, 1);	// 根据索引获得数组中的值
        cJSON_ReplaceItemInObject(arrObj, "game", cJSON_CreateString("中国象棋"));
        cJSON_ReplaceItemInObject(arrObj, "price", cJSON_CreateNumber(99.9));
    }

    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "like");
    if (item != NULL) {
        cJSON *obj = item->child;	// 获得 { "game": "马里奥", "price": 66.6 }

        while (obj) {
            if (obj->type == cJSON_Object) {

                cJSON *objValue = obj->child;	// 获得 "game": "马里奥"
                while (objValue) {

                    // 再通过类型去区分
                    if (objValue->type == cJSON_String) {
                        char *v_str = objValue->valuestring;
                        printf("%s = %s\n", objValue->string, v_str);

                    } else if (objValue->type == cJSON_Number) {
                        double v_double = objValue->valuedouble;
                        printf("%s = %.2f\n", objValue->string, v_double);
                    }
                    // 获取下一个元素
                    objValue = objValue->next;
                }
            }
            // 获取下一组元素
            obj = obj->next;
        }
    }



    /*
        "education": [				修改后：	"education": [
            [ "小学", "初中" ],		====>			[ "小学六年级", "初中初三" ],
            [ "高中", "大学" ]						[ "高中高三", "大学大四" ]
        ],										],
    */
    item = cJSON_GetObjectItem(root, "education");
    if (item != NULL) {
        cJSON *arrArr = NULL;

        arrArr = cJSON_GetArrayItem(item, 0);	// 根据索引获得数组中的值
        cJSON_ReplaceItemInArray(arrArr, 0, cJSON_CreateString("小学六年级"));
        cJSON_ReplaceItemInArray(arrArr, 1, cJSON_CreateString("初中初三"));

        arrArr = cJSON_GetArrayItem(item, 1);	// 根据索引获得数组中的值
        cJSON_ReplaceItemInArray(arrArr, 0, cJSON_CreateString("高中高三"));
        cJSON_ReplaceItemInArray(arrArr, 1, cJSON_CreateString("大学大四"));
    }

    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "education");
    if (item != NULL) {
        cJSON *arr = item->child;	// 获得 [ "小学", "初中" ]

        while (arr) {
            if (arr->type == cJSON_Array) {
                cJSON *arrValue = arr->child;	// 获得 "小学"
                while (arrValue) {
                    if (arrValue->type == cJSON_String) {
                        char *v_str = arrValue->valuestring;
                        printf("education = %s\n", v_str);
                    }
                    arrValue = arrValue->next;	// 获取下一个元素
                }
            }
            // 获取下一组
            arr = arr->next;
        }
    }



    /*
        "languages": {											  修改后：	   "languages": {
            "serialOne": { "language": "汉语", "grade": 10 },	   ====>	   		"serialOne": { "language": "粤语", "grade": 9 },
            "serialTwo": { "language": "英语", "grade": 6}							"serialTwo": { "language": "白话", "grade": 8 }
        },																	   },
    */
    item = cJSON_GetObjectItem(root, "languages");
    if (item != NULL) {
        cJSON *obj = NULL;

        obj = cJSON_GetObjectItem(item, "serialOne");
        // 使用cJSON_ReplaceItemInObject可以直接进行修改
        cJSON_ReplaceItemInObject(obj, "language", cJSON_CreateString("粤语"));
        cJSON_ReplaceItemInObject(obj, "grade", cJSON_CreateNumber(9));

        obj = cJSON_GetObjectItem(item, "serialTwo");
        // 使用cJSON_ReplaceItemInObject可以直接进行修改
        cJSON_ReplaceItemInObject(obj, "language", cJSON_CreateString("白话"));
        cJSON_ReplaceItemInObject(obj, "grade", cJSON_CreateNumber(8));
    }

    // 解析打印查看是否修改成功
    item = cJSON_GetObjectItem(root, "languages");
    if (item != NULL) {
        // 获取到languages里的第一个子元素
        cJSON *obj = item->child;	// 也就是："serialOne": { "language": "汉语", "grade": 10 }

        while (obj) {
            if (obj->type == cJSON_Object) {

                // 获取到子元素的子元素
                cJSON *value = obj->child;	// 也就是：{ "language": "汉语", "grade": 10 }

                while (value) {
                    if (value->type == cJSON_String) {
                        printf("%s = %s\n", value->string, value->valuestring);

                    } else if (value->type == cJSON_Number) {
                        printf("%s = %d\n", value->string, value->valueint);
                    }
                    // 通过next可以自由获取里面的元素了
                    value = value->next;
                }
            }

            obj = obj->next;
        }
    }


    // 打开文件
    file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Open file fail！\n");

        // 释放指针内存
        cJSON_Delete(root);
        return;
    }

    char *cjValue = cJSON_Print(root);
    // 写入文件
    int ret = fwrite(cjValue, sizeof(char), strlen(cjValue), file);
    if (ret == 0) {
        printf("写入文件失败！\n");
    }

    fclose(file);
    free(cjValue);

    // 使用了cJSON_Parse之后，记得调用cJSON_Delete函数释放
    cJSON_Delete(root);
}

void delJson() {

    // 打开文件
    FILE *file = NULL;
    file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Open file fail！\n");
        return;
    }


    // 获得文件大小
    struct stat statbuf;
    stat(FILE_NAME, &statbuf);
    int fileSize = statbuf.st_size;
    printf("文件大小：%d\n", fileSize);


    // 分配符合文件大小的内存
    char *jsonStr = (char *)malloc(sizeof(char) * fileSize + 1);
    memset(jsonStr, 0, fileSize + 1);


    // 读取文件中的json字符串
    int size = fread(jsonStr, sizeof(char), fileSize, file);
    if (size == 0) {
        printf("读取文件失败！\n");
        fclose(file);
        return;
    }
    printf("%s\n", jsonStr);
    fclose(file);


    // 将读取到的json字符串转换成json变量指针
    cJSON *root = cJSON_Parse(jsonStr);
    if (!root) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        free(jsonStr);
        return;
    }
    free(jsonStr);



    cJSON *item = NULL;


    /* 删除： "name":	"小红" */
    // 使用这个函数直接进行删除
    cJSON_DeleteItemFromObject(root, "name");	// 通过键进行删除



    /* 删除：
        "interest":	{
            "badminton":	"林丹"
        }
    */
    item = cJSON_GetObjectItem(root, "interest");
    // 获取到对应的节点对象就可以直接删除了
    if (item != NULL) {
        cJSON_DeleteItemFromObject(item, "badminton");
    }



    /* 删除： "color":	["blue"] */
    item = cJSON_GetObjectItem(root, "color");
    // 获取到对应的节点数组就可以直接删除了
    if (item != NULL) {
        cJSON_DeleteItemFromArray(item, 1);	// 通过索引进行删除
    }



    /* 删除：
        "like":	[
            { "game":	"炸弹人", "price":	88.800000 },
        ]
    */
    item = cJSON_GetObjectItem(root, "like");
    if (item != NULL) {
        cJSON_DeleteItemFromArray(item, 0);


        //cJSON *arrObj = cJSON_GetArrayItem(item, 0);	// 根据索引获得数组中的值
        //if (arrObj != NULL) {
        //	cJSON_DeleteItemFromObject(arrObj, "price");
        //}
    }



    /* 删除： "education":	[["高中高三", "大学大四"]] */
    item = cJSON_GetObjectItem(root, "education");
    if (item != NULL) {
        cJSON_DeleteItemFromArray(item, 1);


        //cJSON *arrArr = cJSON_GetArrayItem(item, 0);	// 根据索引获得数组中的值
        //if (arrArr != NULL) {
        //	cJSON_DeleteItemFromArray(arrArr, 1);
        //}
    }



    /* 删除
        "languages":	{
            "serialTwo":	{ "language":"白话", "grade":8 }
        }
    */
    item = cJSON_GetObjectItem(root, "languages");
    if (item != NULL) {
        cJSON_DeleteItemFromObject(item, "serialTwo");
        //cJSON *obj = cJSON_GetObjectItem(item, "serialOne");
        //if (obj != NULL) {
        //	cJSON_DeleteItemFromObject(obj, "grade");
        //}
    }




    // 打开文件
    file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Open file fail！\n");

        // 释放指针内存
        cJSON_Delete(root);
        return;
    }

    char *cjValue = cJSON_Print(root);
    // 写入文件
    int ret = fwrite(cjValue, sizeof(char), strlen(cjValue), file);
    if (ret == 0) {
        printf("写入文件失败！\n");
    }

    fclose(file);
    free(cjValue);

    // 使用了cJSON_Parse之后，记得调用cJSON_Delete函数释放
    cJSON_Delete(root);
}
