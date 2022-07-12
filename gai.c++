#include <iostream>
#include <list>

// структура содержит номер автомобиля
// и список правонарушений этого автомобиля
// также указатели на левое, правое поддерево и на родителя
struct Gai
{
    std::string numberAuto;
    std::list<std::string> offense;
    Gai *left, *right, *parent;
};

class BinaryTree
{
public:
    // конструктор без параметров
    BinaryTree() : root{nullptr}
    {}

    ~BinaryTree();

    // получить узел
    Gai* getRoot()const { return this->root; }

    // добавляем правонарушение
    void add(std::string number_auto, std::string offense);

    // поиск автомобиял в дереве
    Gai* search(std::string numberAuto);
    // печать дерева

    // очистить
    void clear();

    // вывести всё
    void print(Gai* temp);

    // выводим нарушения по номеру авто
    void print(std::string numberAuto);
    
private:
    Gai* root;
};

void BinaryTree::clear()
{
    Gai* temp = this->root;
    Gai* t{nullptr};
    while (temp != nullptr)
    {
        t = temp->parent;
        if(temp->left == nullptr && temp->right == nullptr)
        {
            if(temp == this->root)
            {
                delete temp;
                temp = nullptr;
                this->root = nullptr;
                return;
            }
            if(temp == t->left)
                t->left = nullptr;
            else t->right = nullptr;
            delete temp;
            temp = t;
        }
        else if(temp->right != nullptr)
        {
            temp = temp->right;
        }
        else if(temp->left != nullptr)
        {
            temp = temp->left;
        }
    }
}

BinaryTree::~BinaryTree()
{
    this->clear();
}

void BinaryTree::add(std::string number_auto, std::string offense)
{
    // если дерево пусто
    if (this->root == nullptr)
    {
        this->root = new Gai{};
        this->root->numberAuto = number_auto;
        this->root->offense.push_back(offense);
        this->root->left = nullptr;
        this->root->right = nullptr;
        this->root->parent = nullptr;
    }
    else
    {
        // если в дереве уже имеются узлы
        Gai* temp = this->root;
        Gai* y = nullptr;
        while (temp != nullptr)
        {
            // сравнение праводим по номеру авто
            // если меньше идем влево, если больше вправо
            y = temp;
            if (number_auto < temp->numberAuto)
                temp = temp->left;
            else if (number_auto > temp->numberAuto)
                temp = temp->right;
            else 
            {
                // если авто с таким номером уже существует в дереве
                // то добавляем нарушение в его список правонарушений
                temp->offense.push_back(offense);
                return;
            }
        }

        // если такого номера в дереве нет
        // то создаем новый узел
        temp = new Gai{};
        // добавляем номер и нарушение в узел
        temp->numberAuto = number_auto;
        temp->offense.push_back(offense);
        temp->left = nullptr;
        temp->right = nullptr;

        // указываем родителя
        temp->parent = y;
        // если номер больше то добавляем вправо от родителя
        // иначе влево
        if (temp->numberAuto > y->numberAuto)
            y->right = temp;
        else
        {
            y->left = temp;
        }
    }
}


Gai* BinaryTree::search(std::string numberAuto)
{
    Gai* temp = this->root;
    while (temp != nullptr)
    {
        if(numberAuto < temp->numberAuto)
            temp = temp->left;
        else if(numberAuto > temp->numberAuto)
            temp = temp->right;
        // если номер есть в списке, то возвращаем указатель на узел
        else return temp;
    }

    // если номера в списке нет, то возвращаем nullptr
    return nullptr;
}

void BinaryTree::print(Gai* temp)
{
    if (temp != nullptr)
    {
        print(temp->left);
        std::cout << "\t номер автомобиля: " << temp->numberAuto << std::endl;
        std::cout << "Список правонаруший:\n";
        for (auto el : temp->offense)
        {
            std::cout << "\t\t" << el << std::endl;
        }
        std::cout << std::endl;
        print(temp->right);
    }
}

void BinaryTree::print(std::string numberAuto)
{
    Gai* temp = this->search(numberAuto);
    if(temp != nullptr)
    {
        std::cout << "\t номер автомобиля: " << temp->numberAuto << std::endl;
        std::cout << "Список правонаруший:\n";
        for (auto el : temp->offense)
        {
            std::cout << "\t\t" << el << std::endl;
        }
        return;
    }

    std::cout << "Номер " << numberAuto << " отсутствует в списке нарушителей!";
}


int main()
{
    BinaryTree listOffense;
    listOffense.add("A771EO69", "не пропустил пешехода!");
    listOffense.add("O137TT69", "проехал на красный!");
    listOffense.add("A777AA69", "превышение скорости!");
    listOffense.add("A777AA69", "проехал на красный!");
    listOffense.add("A777AA69", "двойная сплошная!");
    listOffense.print(listOffense.getRoot());
    std::cout << "------------------------------------------\n";
    listOffense.print("A777AA69");
    listOffense.print("A771AA69");
    
    return 0;
}