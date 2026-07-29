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
            check_char(c);
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
            check_char(c);
            int index = c - 'a';
            if (current_room->neighbours[index])
                current_room = current_room->neighbours[index];
            else 
                return false;
        }
        return true;
    }


    void cleaning(tree_node *current , int index = 0)
    {
        int i = 0;
        tree_node *croot = current ;

        if (croot == NULL || index == 26)
            return;

        if (croot.neighbours[index])
        {
            cleaning(croot->neighbours[index], 0);
            delete croot->neighbours[index];
        }
        cleaning(croot, index + 1);

    }


    
    void    remove(std::string &word, tree_node *head, int startIndex)
    {
        int index = 0; 
        char c ;
        tree_node *curr = head;
        int count = 0;

        if (word.empty())
            return ;

        c = word[startIndex];
        check_char(c);

        index = c - 'a';

        if (curr->neighbours[index] != NULL)
        {
            if (startIndex == word.size() - 1)
                curr->neighbours[index]->isWord = false;
            remove(word, curr->neighbours[index], startIndex + 1);

            for (int i = 0 ; i < 26 ; i++)
            {   
                if (count >= 1)
                 break;
                if (curr->neighbours[index] && curr->neighbours[index]->neighbours[i] != NULL)
                    count++;        
            }

            if (count >= 1)
                return ;
            else
            {
                delete curr->neighbours[index];
                curr->neighbours[index] = NULL;
                return ;
            }
        }

        return ;
        
    }

    
    ~tries()
    {
        cleaning(root , 0);
        delete root;
        root = NULL;
    }

    bool check_char(char &c)
    {
        if (!isalpha(c))
                    throw std::runtime_error("Error: Input is not an alphabet letter.");
        c = tolower(c);
    }

};




#endif