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

    void insert(std::string &input)
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

    bool search(std::string &word)
    {
        if (!root)
            return false;

        tree_node *current_room = root;
        int i = 0;
        char c ;

        for (; i < word.size(); i++)
        {
            c = word[i];
            if (!isalpha(c))
                    throw std::runtime_error("Error: Input is not an alphabet letter.");
            c = tolower(c);
            int index = c - 'a';
            if (current_room->neighbours[index])
                current_room = current_room->neighbours[index];
            else 
                return false;
        }
        return current_room.isWord;
    }

    bool startwith(std::string &word)
    {
           if (!root)
            return false;

        tree_node *current_room = root;
        int i = 0;
        char c ;
        for (; i < word.size(); i++)
        {
            c = word[i];
            if (!isalpha(c))
                    throw std::runtime_error("Error: Input is not an alphabet letter.");
            c = tolower(c);
            int index = c - 'a';
            if (current_room->neighbours[index])
                current_room = current_room->neighbours[index];
            else 
                return false;
        }
        return true;
    }


    void cleaning(tree **croot , int index = 0)
    {
        int i = 0;

        if (croot == NULL || index == 26)
            return;

        if (*croot.neighbours[index])
        {
            *croot = croot->neighbours[index];
            cleaning(croot , index);
            delete croot->neighbours[index];
        }
        else 
            cleaning(index + 1);
        delete(croot);
    }


    ~tries()
    {

    }

};




#endif