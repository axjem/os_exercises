#include <iostream>
#include <sstream>
#include <map>
using namespace std;

template<typename T>
string to_string(T value) {
    ostringstream os;
    os << value;
    return os.str();
}

// 节点数据结构，能够连接前和后两方向的Node
struct Node {
    int start;
    int size;
    Node *pre, *next;
    Node(int _start=0, int _size=0) : start(_start), size(_size), pre(NULL), next(NULL) {}
};

// 建构三个Node的顺序关系，使得有node1 -> node2 -> node3
void adjust(Node* node1, Node* node2, Node* node3) {
    node2->pre = node1;
    node2->next = node3;
    node1->next = node2;
    node3->pre = node2;
}

// 输出Node信息
void display(string name, Node* node) {
    cout << name << ": ";
    cout << '(' << node->start << ", ";
    cout << node->size << ')' << endl;
}

// 列表结构
struct List {
    Node *super_header, *super_trailer;
    List(int size) {
        super_header = new Node();
        super_trailer = new Node();
        super_header->next = super_trailer;
        super_trailer->pre = super_header;
        Node* node = new Node(0, size);
        adjust(super_header, node, super_trailer);
    }
    void insert(Node* node) {
        if (!node) return;
        if (empty()) {      // empty
            adjust(super_header, node, super_trailer);
        }
        else {
            Node* last_node = super_trailer->pre;
            if (node->start > last_node->start) {       // 应该插到最后一个位置
                if (last_node->start + last_node->size == node->start) {
                    last_node->size += node->size;
                    delete(node);
                }
                else {
                    adjust(last_node, node, super_trailer);
                }
            }
            else {
                Node* cur_node = super_header->next;
                bool merge_flag = false;
                while (cur_node != super_trailer) {
                    if (cur_node->start > node->start) {
                        Node* pre_node = cur_node->pre;
                        if (pre_node != super_header && pre_node->start + pre_node->size == node->start) {      // 可以和前面合并
                            merge_flag = true;
                            pre_node->size += node->size;
                            delete(node);
                            node = pre_node;
                            pre_node = node->pre;
                        }
                        if (node->start + node->size == cur_node->start) {          // 可以和后面合并
                            merge_flag = true;
                            node->size += cur_node->size;
                            adjust(pre_node, node, cur_node->next);
                            delete(cur_node);
                            cur_node = node;
                        }
                        if (!merge_flag) {
                            adjust(pre_node, node, cur_node);
                        }
                        break;
                    }
                    cur_node = cur_node->next;
                }
            }
        }
    }
    bool empty() {
        return super_header->next == super_trailer;
    }
    Node* first() {
        if (!empty())
            return super_header->next;
        else
            return NULL;
    }
};

// 输出一个列表的信息，依序输出其中的节点Node信息
void display_list(List* node_list) {
    cout << "free list: " << endl;
    if (node_list->empty()) {
        cout << "empty..." << endl;
        return;
    }
    int no = 0;
    string name_pre = "node";
    Node* node = node_list->first();
    while (node != node_list->super_trailer) {
        string name = "  ";
        name += name_pre;
        name += to_string(no ++);
        display(name, node);
        node = node->next;
    }
}


Node* mem_malloc(List* node_list, int size) {
    if (node_list->empty()) return NULL;

    Node* cur_node = node_list->first();
    Node* best_node = NULL;
    while (cur_node != node_list->super_trailer) {
        if (cur_node->size < size) {
            cur_node = cur_node->next;
            continue;
        }
        if (best_node && cur_node->size >= best_node->size) {
            cur_node = cur_node->next;
            continue;
        }
        best_node = cur_node;
        cur_node = cur_node -> next;
    }
    if (!best_node) return NULL;
    Node* res = new Node(best_node->start, size);
    if (best_node->size == size) {
        (best_node->pre)->next = best_node->next;
        (best_node->next)->pre = best_node->pre;
        delete(best_node);
    }
    else {
        best_node->size -= size;
        best_node->start += size;
    }
    return res;
}

void mem_free(List* list, Node* node) {
    cout << "mem_free: " << endl;
    display("node", node);
    list->insert(node);
}

void display_using(map<int, Node*> using_nodes) {
    cout << "using nodes: " << endl;
    if (using_nodes.empty()) {
        cout << "empty..." << endl;
        return;
    }
    map<int, Node*>::iterator it = using_nodes.begin();
    while (it != using_nodes.end()) {
        string name = "  ";
        name += to_string(it->first);
        display(name, it->second);
        it ++;
    }
}


int main() {
    int size = 0;
    map<int, Node*> using_nodes;
    map<int, Node*>::iterator it;

    cout << "请输入内存总大小：" << endl;
    cin >> size;
    List* node_list = new List(size);

    cout << "Usage: op <n>" << endl;
    cout << "如：M 1，表示申请大小为1的内存" << endl;
    cout << "    F 1，表示释放标号为1的块" << endl;
    cout << "    D，查看当前内存分配情况" << endl;
    cout << "    N，退出" << endl;

    char op = 'Y';
    int num = 0, no = 0;
    while (op != 'N') {
         cin >> op;
         if (op == 'M') {
            cin >> size;
            Node* node = mem_malloc(node_list, size);
            if (node) {
                using_nodes.insert(pair<int, Node*>(num, node));
                num ++;
            }
            else {
                cout << "分配失败！" << endl;
                display_list(node_list);
            }
         }
         else if (op == 'F') {
            cin >> no;
            it = using_nodes.find(no);
            if (it == using_nodes.end()) {
                 cout << "没有这个node，不能释放" << endl;
                 display_using(using_nodes);
            }
            else {
                Node* node = it->second;
                using_nodes.erase(it);
                mem_free(node_list, node);
            }
         }
         else if (op == 'D') {
            display_list(node_list);
            display_using(using_nodes);
         }
    }
    return 0;
}
