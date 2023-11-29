#include <cstddef>

// 定义 DestructionObserverTag
struct DestructionObserverTag {};

// 定义 IntrusiveListNode，表示链表节点
template <typename Tag> class IntrusiveListNode {
public:
  IntrusiveListNode() : next(nullptr), prev(nullptr) {}

  // 嵌入式链表节点的指针，表示下一个和前一个节点
  IntrusiveListNode *next;
  IntrusiveListNode *prev;
};

// 定义 IntrusiveListBase，表示基于侵入式链表的容器
template <typename Tag> class IntrusiveListBase {
public:
  IntrusiveListBase() : head(nullptr), tail(nullptr) {}

  // 在链表尾部添加节点
  void Append(IntrusiveListNode<Tag> *node) {
    if (!head) {
      // 如果链表为空，直接设置头尾为当前节点
      head = tail = node;
    } else {
      // 否则，在尾部追加节点
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
  }

  // 在链表中移除节点
  void Remove(IntrusiveListNode<Tag> *node) {
    if (node->prev) {
      // 如果存在前一个节点，调整前一个节点的 next 指针
      node->prev->next = node->next;
    } else {
      // 否则，更新头指针
      head = node->next;
    }

    if (node->next) {
      // 如果存在下一个节点，调整下一个节点的 prev 指针
      node->next->prev = node->prev;
    } else {
      // 否则，更新尾指针
      tail = node->prev;
    }
  }

  void unlink() {
    // TODO:
  }

private:
  // 链表头指针和尾指针
  IntrusiveListNode<Tag> *head;
  IntrusiveListNode<Tag> *tail;
};

// 定义 DestructionObserver，继承 IntrusiveListBase
// class DestructionObserver : public IntrusiveListNode<DestructionObserverTag>
// { public:
//   virtual void WillDestruct() = 0;
//   virtual ~DestructionObserver() {}
// };
