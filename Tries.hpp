#ifndef TRIES_HPP
#define TRIES_HPP

#include <map>
#include <unordered_map>
#include <string.h>
#include <stdexcept> 
#include <iostream>
#include <cctype>  

#define MAX_CHARS 256


typedef struct node
{
    struct node *neighbours[26];
    bool isWord = false;
} tree_node;


class tries 
{
    
    tree_node *root;
    
    public :

        tries()
        {
            root = NULL;
        }
        tries(std::string &input)
        {
            root = create_node();
            insert(input);
        }


    tree_node *create_node()
    {
        root = new tree_node();
        memset(root->neighbours , 0 , sizeof(tree_node *) * 26);
        return root;
    }

    void insert(const std::string &input)
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
            current_room->isWord = true;
        return;
    }

    bool search(const std::string &word)
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
        return current_room->isWord;
    }

    bool startwith(const std::string &word)
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

        if (croot->neighbours[index])
        {
            cleaning(croot->neighbours[index], 0);
            delete croot->neighbours[index];
        }
        cleaning(croot, index + 1);

    }


    
    bool    remove(const std::string &word, tree_node *head, int startIndex)
    {
        int index = 0; 
        char c ;
        tree_node *curr = head;
        int count = 0;

        if (word.empty())
            return false;

        if (startIndex == word.size())
        {
            curr->isWord = false;
            if (has_neighbours(curr))
                return false;
            else
                return true;
        }

        c = word[startIndex];
        check_char(c);
        index = c - 'a';

        if (curr->neighbours[index] != NULL)
        {
            bool status = remove(word, curr->neighbours[index], startIndex + 1);
            if (status)
            {  delete curr->neighbours[index];
                curr->neighbours[index] = NULL;
            }
            if (has_neighbours(curr) || curr->isWord)
                return false;
            return true;
        }
        return false;
    }

    
    ~tries()
    {
        cleaning(root , 0);
        delete root;
        root = NULL;
    }

    bool check_char(const char &c)
    {
        if (!isalpha(c))
                    throw std::runtime_error("Error: Input is not an alphabet letter.");
        c = tolower(c);
    }

    bool has_neighbours(tree_node *head)
    {
        int count  = 0;
        tree_node *curr = head ;

        for (int i = 0 ; i < 26 ; i++)
        {   
            if (count >= 1)
             return true;
            if (curr && curr->neighbours[i] != NULL)
                count++;        
        }
        return false;
    }
    tree_node *&get_root()
    {
        return root;
    }



};




#endif