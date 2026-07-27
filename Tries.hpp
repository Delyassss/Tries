#ifndef TRIES_HPP
#define TRIES_HPP

#include <map>
#include <unordered_map>
#include <string.h>
#include <stdexcept> 
#include <iostream>
#include <cctype>  

#define MAX_CHARS 256

typedef unordered_map<char, tree_node> Tree;



typedef struct node
{
    struct node *neighbours[26];
    bool isWord = false;
} tree_node;


class tries 
{
    
   struct  tree_node *root;
   Tree head;
    
    public :

    tree_node *create_node()
    {
        root = new tree_node();
        bzero(&root.neighbours, sizeof(tree_node *) * 26);
        return root;
    }

    void insert(std::string input)
    {
        if (!root)
            root =  create_node();

        tree_node* current_room = root;
            
        for (int i = 0; i < input.size() ; i++)
         {
            if (!isalpha(input[i]))
                    throw std::runtime_error("Error: Input is not an alphabet letter.");
            int index = input[i] - 'a';

            input[i] = tolower(input[i]);
                
            if (current_room->neighbours[index] == NULL)
                current_room->neighbours[index] = create_node();

                current_room = current_room->neighbours[index];
        }
            current_room.isWord = true;
        return;
    }




};




#endif