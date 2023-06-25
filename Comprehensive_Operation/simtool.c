/**
  ******************************************************************************
  * @file           : simtool.c
  * @author         : YuwenTianhao
  * @brief          : 大规模文档去重分析
  * @attention      : None
  * @date           : 2023/6/6
  ******************************************************************************
  */

// 以下为加速作弊码

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse3", "sse2", "sse")
#pragma GCC target("avx", "sse4", "sse4.1", "sse4.2", "ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline", "fast-math", "unroll-loops", "no-stack-protector")
#pragma GCC diagnostic error "-fwhole-program"
#pragma GCC diagnostic error "-fcse-skip-blocks"
#pragma GCC diagnostic error "-funsafe-loop-optimizations"
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTICLE_NUM 1000000 // 最大文章数量
#define MAX_DIC_TREE_NODE 1000000 // 最大字典树结点数量
#define MAX_STOPWORD_STREAM 2000000 // 最大停用词流
#define MAX_ARTICLE_STREAM 50000000 // 最大文章流；不能再小
#define MAX_HASH_STREAM 2000000 // 最大哈希值文件流
#define MAX_N_LENGTH 100000 // 最大特征向量长度
#define MAX_WORD_LENGTH 800 // 最大单词长度
#define MAX_WORDS_NUM 2000000 // 最大不同单词数量
#define MAX_ARTICLE_NAME_LENGTH 100 // 最大文档序号长度

#define is_letter(ch) ( ((ch)>='a' && (ch)<='z') || ((ch)>='A' && (ch)<='Z') ) // 判断字母宏定义
#define is_alnum(c) (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9'))) // 判断字母或数字宏定义
#define c_tolower(c) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c) // 字符大写转小写宏定义

int N; // 特征向量长度
int M; // 指纹长度
int ART_NUM; // 文章总数
int S_NUM; // Sample（待查重）总数
int Hash_table_length; // “hashvalue.txt”中一行的长度
// 为使得性能最佳，必须使用空间换时间，需要在全局开较大数组如下

char STOP_STREAM[MAX_STOPWORD_STREAM]; // 停止词流
char ARTICLE_STREAM[MAX_ARTICLE_STREAM]; // 文章流
char HASH_STREAM[MAX_HASH_STREAM]; // 哈希值文件流

// 特征向量
typedef struct
{
    char word[MAX_WORD_LENGTH]; // 单词：用于字典序排序
    int weight; // 权重：题目中解释为词频
} Feature;
Feature feature[MAX_WORDS_NUM]; // 特征向量-数组形式
int feature_ind;

// 文章记录
typedef struct artical_list_element
{
    // 文档序号
    char name[MAX_ARTICLE_NAME_LENGTH];
    // 文章指纹 : 128位
    unsigned long long fingerprint[4];
} Aelement;
Aelement A_LIST[MAX_ARTICLE_NUM]; // 文章列表
Aelement S_LIST[MAX_ARTICLE_NUM / 100]; // Sample列表

// 字典树结点
typedef struct
{
    int iNext[26]; // 字典树孩子的下标位置
    int fre_q; // 词频数量，同时也标记停止位
    int index; // 字典树在特征向量中的序号：F_TREE专用
} DTnode;
DTnode D_TREE[MAX_DIC_TREE_NODE]; // 字典树
DTnode F_TREE[MAX_DIC_TREE_NODE / 10]; // 特征向量树

char hamming_0[1000][MAX_ARTICLE_NAME_LENGTH];
char hamming_1[1000][MAX_ARTICLE_NAME_LENGTH];
char hamming_2[1000][MAX_ARTICLE_NAME_LENGTH];
char hamming_3[1000][MAX_ARTICLE_NAME_LENGTH];

/*
 * qsort比较函数
 */
int cmp_function(const void *e1, const void *e2)
{
    Feature *f1 = (Feature *) e1;
    Feature *f2 = (Feature *) e2;
    if (f2->weight == f1->weight)
        return strcmp(f1->word, f2->word);
    return f2->weight - f1->weight;
}


/**
 * @brief 建立停用词树
 * @note 可以先将停用词树的频率设为-1，遇停用词（fre_q = -1）不处理即可
 * @param None
 * @retval 停用词树的尾部
 */
int set_stop_word()
{
    FILE *stopword = fopen("stopwords.txt", "rb");
    int stop_len = fread(STOP_STREAM, sizeof(char), MAX_STOPWORD_STREAM, stopword);
    register int tree_ind = 0, tree_rear = 0, stop_ind = 0;
    do
    {
        while (STOP_STREAM[stop_ind] != '\r' && STOP_STREAM[stop_ind] != '\n' && stop_ind < stop_len)
        {

            if (!D_TREE[tree_ind].iNext[STOP_STREAM[stop_ind] - 'a'])
                D_TREE[tree_ind].iNext[STOP_STREAM[stop_ind] - 'a'] = ++tree_rear;
            tree_ind = D_TREE[tree_ind].iNext[STOP_STREAM[stop_ind] - 'a'];
            stop_ind++;
        }
        D_TREE[tree_ind].fre_q = -1;
        stop_ind += 2;
        tree_ind = 0;
    } while (stop_ind < stop_len);
    fclose(stopword);
    return tree_rear;
}

// 字典树转数组
void TreeToArray(DTnode nowNode, char prefix[], int len)
{
    if (nowNode.fre_q > 0)
    {
        prefix[len] = '\0';
        memcpy(feature[feature_ind].word, prefix, strlen(prefix));
        feature[feature_ind].weight = nowNode.fre_q;
        feature_ind++;
    }
    for (int i = 0; i < 26; i++)
        if (nowNode.iNext[i] > 0)
        {
            prefix[len] = i + 'a';
            TreeToArray(D_TREE[nowNode.iNext[i]], prefix, len + 1);
        }
}

/**
 * @brief 创建特征向量
 * @note 读取文章->词频统计->字典树(D_TREE)转数组(feature[])->排序（qsort）->数组(feature[])转字典树(F_TREE)
 * @param None
 * @retval None
 */
void create_feature_vector(int stop_tree_rear, FILE *article, unsigned long long arti_len)
{

    //read_artical函数内局部寄存器变量
    //arti_ind：当前访问的文档流数组下标
    //arti_cou：文档计数以及编号
    //tree_ind：当前访问的字典树数组下标
    register int arti_ind = 0, tree_ind;
    // 读取全部文章，生成特征向量
    register int Dtree_rear = stop_tree_rear;
    register int Ftree_rear = 0;
    char prefix[10 * MAX_WORD_LENGTH] = "";
    do
    {
        // 非字符进入下一次循环
        if (!is_letter(ARTICLE_STREAM[arti_ind]))
        {
            arti_ind++;
            continue;
        }
            // 字符存入
        else
        {
            tree_ind = 0;
            while (is_letter(ARTICLE_STREAM[arti_ind]) && arti_ind < arti_len)
            {
                register char buffer = c_tolower(ARTICLE_STREAM[arti_ind]);
                if (!D_TREE[tree_ind].iNext[buffer - 'a'])
                    D_TREE[tree_ind].iNext[buffer - 'a'] = ++Dtree_rear;
                tree_ind = D_TREE[tree_ind].iNext[buffer - 'a'];
                arti_ind++;
            }
            if (D_TREE[tree_ind].fre_q != -1)
                D_TREE[tree_ind].fre_q++;
        }
    } while (arti_ind < arti_len);

    // 词频统计
    TreeToArray(D_TREE[0], prefix, 0);
    qsort(feature, feature_ind, sizeof(Feature), cmp_function);

    // 将排序好的数列类型的特征向量 转化成字典树类型
    for (int i = 0; i < N; i++)
    {
        int Ftree_ind = 0;
        for (int j = 0; is_letter(feature[i].word[j]); j++)
        {
            char buffer = feature[i].word[j];
            if (!F_TREE[Ftree_ind].iNext[buffer - 'a'])
                F_TREE[Ftree_ind].iNext[buffer - 'a'] = ++Ftree_rear;
            Ftree_ind = F_TREE[Ftree_ind].iNext[buffer - 'a'];
        }
        F_TREE[Ftree_ind].fre_q = feature[i].weight; // 这里的词频没有意义，取非0值即可
        F_TREE[Ftree_ind].index = i;
    }
}

/**
 * @brief 文章读取
 * @note 每次读取一篇文章并刷新字典树，并对文章生成指纹，存入文章记录中；
 * @param stop_tree_rear： STOP_TREE的最尾部序号
 * @retval 文章的数量
 */
int read_article(int stop_tree_rear, FILE *article, unsigned long long arti_len)
{
    //read_artical函数内局部寄存器变量
    //arti_ind：当前访问的文档流数组下标
    //arti_cou：文档计数以及编号
    //tree_ind：当前访问的字典树数组下标
    register int arti_ind = 0, arti_cou = 0, tree_ind;
    // 2．统计每个网页（文本）的特征向量中每个特征（单词）的频度（权重），得到特征向量对应的权重向量weight
    do
    {
        int signed_weight[MAX_N_LENGTH] = {0}; // 符号化权重向量，长度为N
        register int name_len = 0;

        // 读取'\f'和文档名字间的无用字符的操作以防止文档没有名字
        while (!is_alnum(ARTICLE_STREAM[arti_ind]))
        {
            arti_ind++;
            if (arti_ind >= arti_len)break;
        }
        // 读取名字
        while (ARTICLE_STREAM[arti_ind] != '\r')
            A_LIST[arti_cou].name[name_len++] = ARTICLE_STREAM[arti_ind++];
        do
        {
            // 非字符进入下一次循环
            if (!is_letter(ARTICLE_STREAM[arti_ind]))
            {
                arti_ind++;
                continue;
            }
                // 在字典树（F_TREE）中查找单词：1、未查找到单词（比对失败） 2、查找到但是为中间结点（非单词末尾） 3、查找到该单词
            else
            {
                tree_ind = 0;
                register int flag = 1; // 比对成功标志位
                while (is_letter(ARTICLE_STREAM[arti_ind]))
                {
                    register char buffer = c_tolower(ARTICLE_STREAM[arti_ind]);
                    // 比对到中间失败，跳过该单词
                    if (!F_TREE[tree_ind].iNext[buffer - 'a'])
                    {
                        flag = 0;
                        while (is_letter(ARTICLE_STREAM[arti_ind]) && arti_ind < arti_len)arti_ind++;
                        break;
                    }
                        // 字符比对成功，对下一个比对
                    else
                    {
                        tree_ind = F_TREE[tree_ind].iNext[buffer - 'a'];
                        arti_ind++;
                    }
                }
                if (flag == 1 && F_TREE[tree_ind].fre_q > 0)
                {
                    // 赋值符号化权重向量
                    int index = F_TREE[tree_ind].index;
                    for (int j = 0; j < M; j++)
                    {
                        if (HASH_STREAM[index * (Hash_table_length + 2) + j] == '1') // 相当于查找hash_value[index][j]
                            signed_weight[j]++;
                        else
                            signed_weight[j]--;
                    }
                }
            }
        } while (ARTICLE_STREAM[arti_ind] != '\f' && arti_ind < arti_len); // 文章结束判断

        // 生成特征指纹，为了运行时间多加了不少判断
        // 考虑 M 的大小
        if (M <= 32)
        {
            for (int i = 0; i < M; i++)
                A_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
        }
        else if (32 < M && M <= 64)
        {
            for (int i = 0; i < 32; i++)
                A_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 32; i < M; i++)
                A_LIST[arti_cou].fingerprint[1] |= signed_weight[i] > 0 ? 1 << i : 0;
        }

        else if (64 < M && M <= 96)
        {
            for (int i = 0; i < 32; i++)
                A_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 32; i < 64; i++)
                A_LIST[arti_cou].fingerprint[1] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 64; i < M; i++)
                A_LIST[arti_cou].fingerprint[2] |= signed_weight[i] > 0 ? 1 << i : 0;
        }
        else
        {
            for (int i = 0; i < 32; i++)
                A_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 32; i < 64; i++)
                A_LIST[arti_cou].fingerprint[1] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 64; i < 96; i++)
                A_LIST[arti_cou].fingerprint[2] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 96; i < M; i++)
                A_LIST[arti_cou].fingerprint[3] |= signed_weight[i] > 0 ? 1 << i : 0;
        }

        arti_cou++;
        arti_ind += 3; // 跳过\f\r\n

    } while (arti_ind < arti_len);
    return arti_cou;
}

/**
 * @brief 待查重文章读取
 * @note 每次读取一篇待查重文章并刷新字典树，并对文章生成指纹，存入文章记录中；
 * @param stop_tree_rear： 处理完停用词后的最尾部序号
 * @retval 待查重文章的数量
 */
int read_sample(int stop_tree_rear)
{
    // 最后应该返回文章总数或 赋值给ART_NUM
    FILE *article = fopen("sample.txt", "rb");
    //返回读入了多少元素，作为长度标记
    unsigned long long arti_len = fread(ARTICLE_STREAM, sizeof(char), MAX_ARTICLE_STREAM, article);
    //read_artical函数内局部寄存器变量
    //arti_ind：当前访问的文档流数组下标
    //arti_cou：文档计数以及编号
    //tree_ind：当前访问的字典树数组下标
    register int arti_ind = 0, arti_cou = 0, tree_ind;
    // 2．统计每个网页（文本）的特征向量中每个特征（单词）的频度（权重），得到特征向量对应的权重向量weight
    do
    {
        int signed_weight[MAX_N_LENGTH] = {0}; // 符号化权重向量，长度为N
        register int name_len = 0;

        // 读取'\f'和文档名字间的无用字符的操作以防止文档没有名字
        while (!is_alnum(ARTICLE_STREAM[arti_ind]))
        {
            arti_ind++;
            if (arti_ind >= arti_len)break;
        }
        // 读取名字
        while (ARTICLE_STREAM[arti_ind] != '\r' && arti_ind < arti_len)
            S_LIST[arti_cou].name[name_len++] = ARTICLE_STREAM[arti_ind++];
        do
        {
            // 非字符进入下一次循环
            if (!is_letter(ARTICLE_STREAM[arti_ind]))
            {
                arti_ind++;
                continue;
            }
                // 在字典树（F_TREE）中查找单词：1、未查找到单词（比对失败） 2、查找到但是为中间结点（非单词末尾） 3、查找到该单词
            else
            {

                tree_ind = 0;
                register int flag = 1; // 比对成功标志位
                while (is_letter(ARTICLE_STREAM[arti_ind]))
                {
                    register char buffer = c_tolower(ARTICLE_STREAM[arti_ind]);
                    // 比对到中间失败，跳过该单词
                    if (!F_TREE[tree_ind].iNext[buffer - 'a'])
                    {
                        flag = 0;
                        while (is_letter(ARTICLE_STREAM[arti_ind]) && arti_ind < arti_len)arti_ind++;
                        break;
                    }
                        // 字符比对成功，对下一个比对
                    else
                    {
                        tree_ind = F_TREE[tree_ind].iNext[buffer - 'a'];
                        arti_ind++;
                    }
                }
                if (F_TREE[tree_ind].fre_q > 0 && flag == 1)
                {
                    // 赋值符号化权重向量
                    int index = F_TREE[tree_ind].index;
                    for (int j = 0; j < M; j++)
                    {
                        if (HASH_STREAM[index * (Hash_table_length + 2) + j] == '1') // 相当于查找hash_value[index][j]
                            signed_weight[j]++;
                        else
                            signed_weight[j]--;
                    }
                }
            }
        } while (ARTICLE_STREAM[arti_ind] != '\f' && arti_ind < arti_len); // 文章结束判断
        // 生成特征指纹，为了运行时间多加了不少判断
        // 考虑 M 的大小
        if (M <= 32)
        {
            for (int i = 0; i < M; i++)
                S_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
        }
        else if (32 < M && M <= 64)
        {
            for (int i = 0; i < 32; i++)
                S_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 32; i < M; i++)
                S_LIST[arti_cou].fingerprint[1] |= signed_weight[i] > 0 ? 1 << i : 0;
        }

        else if (64 < M && M <= 96)
        {
            for (int i = 0; i < 32; i++)
                S_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 32; i < 64; i++)
                S_LIST[arti_cou].fingerprint[1] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 64; i < M; i++)
                S_LIST[arti_cou].fingerprint[2] |= signed_weight[i] > 0 ? 1 << i : 0;
        }
        else
        {
            for (int i = 0; i < 32; i++)
                S_LIST[arti_cou].fingerprint[0] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 32; i < 64; i++)
                S_LIST[arti_cou].fingerprint[1] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 64; i < 96; i++)
                S_LIST[arti_cou].fingerprint[2] |= signed_weight[i] > 0 ? 1 << i : 0;
            for (int i = 96; i < M; i++)
                S_LIST[arti_cou].fingerprint[3] |= signed_weight[i] > 0 ? 1 << i : 0;
        }

        arti_cou++;
        arti_ind += 3; // 跳过\f\r\n

    } while (arti_ind < arti_len);

    fclose(article);
    return arti_cou;
}

/**
 * @brief 汉明距离
 * @note 使用 Brian Kernighan 算法，时间复杂度更低
 * @param unsigned long long seq1
 * @param unsigned long long seq2
 * @retval 汉明距离
 */
int hammingDistance(unsigned long long seq1, unsigned long long seq2)
{
    int distance = 0;
    unsigned long long diff = seq1 ^ seq2;
    // 统计不同比特位的个数
    while (diff > 0)
    {
        diff &= (diff - 1);
        distance++;
    }
    return distance;
}

int main(int argc, char *argv[])
{
    N = atoi(argv[1]);
    M = atoi(argv[2]);

    FILE *article = fopen("article.txt", "rb");
    //返回读入了多少元素，作为长度标记
    unsigned long long arti_len = fread(ARTICLE_STREAM, sizeof(char), MAX_ARTICLE_STREAM, article);

    FILE *hashvalue = fopen("hashvalue.txt", "rb");
    fread(HASH_STREAM, sizeof(char), MAX_HASH_STREAM, hashvalue);

    // 检查"hashvalue.txt"的一行的 0 1 个数（不是很优美，但是能用）
    for (int i = 0; HASH_STREAM[i] != '\n'; i++)
        Hash_table_length++;
    Hash_table_length--;

    // 建立停用词树
    int stop_tree_rear = set_stop_word(); // STOP树线性表的尾部序号

    // 1．获取网页特征向量
    create_feature_vector(stop_tree_rear, article, arti_len);

    // 查重文章读取
    ART_NUM = read_article(stop_tree_rear, article, arti_len);

    // 待查重文章读取
    S_NUM = read_sample(stop_tree_rear);

    fclose(article);

    // 比对过程
    FILE *result = fopen("result.txt", "w");
    register int i, j; // 循环变量 i:遍历S_LIST  j:遍历A_LIST
    for (i = 0; i < S_NUM; i++)
    {
        fprintf(result, "%s\n", S_LIST[i].name);
        if (i == 0)printf("%s\n", S_LIST[i].name);

        register int ind_0 = 0, ind_1 = 0, ind_2 = 0, ind_3 = 0;
        for (j = 0; j < ART_NUM; j++)
        {
            register int hamming_distance = 0;
            hamming_distance += hammingDistance(S_LIST[i].fingerprint[0], A_LIST[j].fingerprint[0]);
            if (M > 32)
                hamming_distance += hammingDistance(S_LIST[i].fingerprint[1], A_LIST[j].fingerprint[1]);
            if (M > 64)
                hamming_distance += hammingDistance(S_LIST[i].fingerprint[2], A_LIST[j].fingerprint[2]);
            if (M > 96)
                hamming_distance += hammingDistance(S_LIST[i].fingerprint[3], A_LIST[j].fingerprint[3]);
            switch (hamming_distance)
            {
                case 0:
                    memcpy(hamming_0[ind_0++], A_LIST[j].name, MAX_ARTICLE_NAME_LENGTH - 10);
                    break;
                case 1:
                    memcpy(hamming_1[ind_1++], A_LIST[j].name, MAX_ARTICLE_NAME_LENGTH - 10);
                    break;
                case 2:
                    memcpy(hamming_2[ind_2++], A_LIST[j].name, MAX_ARTICLE_NAME_LENGTH - 10);
                    break;
                case 3:
                    memcpy(hamming_3[ind_3++], A_LIST[j].name, MAX_ARTICLE_NAME_LENGTH - 10);
                    break;
                default:
                    break;
            }
        }
        if (ind_0 != 0)
        {
            fprintf(result, "0:");
            register int k = 0;
            while (k < ind_0)
                fprintf(result, "%s ", hamming_0[k++]);
            fprintf(result, "\n");
            if (i == 0)
            {
                printf("0:");
                k = 0;
                while (k < ind_0)
                    printf("%s ", hamming_0[k++]);
                printf("\n");
            }
        }
        if (ind_1 != 0)
        {
            fprintf(result, "1:");
            register int k = 0;
            while (k < ind_1)
                fprintf(result, "%s ", hamming_1[k++]);
            fprintf(result, "\n");
            if (i == 0)
            {
                printf("1:");
                k = 0;
                while (k < ind_1)
                    printf("%s ", hamming_1[k++]);
                printf("\n");
            }
        }
        if (ind_2 != 0)
        {
            fprintf(result, "2:");
            register int k = 0;
            while (k < ind_2)
                fprintf(result, "%s ", hamming_2[k++]);
            fprintf(result, "\n");
            if (i == 0)
            {
                printf("2:");
                k = 0;
                while (k < ind_2)
                    printf("%s ", hamming_2[k++]);
                printf("\n");
            }
        }
        if (ind_3 != 0)
        {
            fprintf(result, "3:");
            register int k = 0;
            while (k < ind_3)
                fprintf(result, "%s ", hamming_3[k++]);
            fprintf(result, "\n");
            if (i == 0)
            {
                printf("3:");
                k = 0;
                while (k < ind_3)
                    printf("%s ", hamming_3[k++]);
                printf("\n");
            }
        }

    }
    fclose(result);

    return 0;
}
