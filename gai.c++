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

    // получить узел
    Gai* getRoot()const { return this->root; }

    // добавляем правонарушение
    BinaryTree add(std::string number_auto, std::string offense);

    // поиск автомобиял в дереве
    Gai* search(std::string numberAuto);
    // печать дерева
    void print(Gai* temp);

    // выводим нарушения по номеру авто
    void print(std::string numberAuto);


private:
    Gai* root;
};

BinaryTree BinaryTree::add(std::string number_auto, std::string offense)
{
    // если дерево пусто
    if (root == nullptr)
    {
        root = new Gai{};
        root->numberAuto = number_auto;
        root->offense.push_back(offense);
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
    }
    else
    {
        // если в дереве уже имеются правонарушения
        Gai* temp = root;
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
                return *this;
            }
        }

        // если такого номера в дереве нет
        // то создаем новый узел
        Gai* newOffense = new Gai{};
        // добавляем номер и нарушение в узел
        newOffense->numberAuto = number_auto;
        newOffense->offense.push_back(offense);
        newOffense->left = nullptr;
        newOffense->right = nullptr;

        // указываем родителя
        newOffense->parent = y;

        // если номер больше то добавляем вправо от родителя
        // иначе влево
        if (newOffense->numberAuto > y->numberAuto)
            y->right = newOffense;
        else
        {
            y->left = newOffense;
        }
    }

    // возвращаем сам объект
    return *this;
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
    listOffense.add("A771EO69", "не пропустил пешехода!").add("O137TT69", "проехал на красный!");
    listOffense.add("A777AA69", "превышение скорости!");
    listOffense.add("A777AA69", "проехал на красный!");
    listOffense.add("A777AA69", "двойная сплошная!");
    listOffense.print(listOffense.getRoot());
    std::cout << "------------------------------------------\n";
    listOffense.print("A777AA69");
    listOffense.print("A771AA69");

    return 0;
}