#include <iostream>
#include <cstdlib>
#include "p2.h"
#include "recursive.h"

using namespace std;

int size(list_t list){
    if (list_isEmpty(list)){
        return 0;
    }
    else
    {
        return 1 + size(list_rest(list)) ;
    }
}

int sum(list_t list){
    if (list_isEmpty(list)){
        return 0;
    }
    else
    {
        return list_first(list) + sum(list_rest(list)) ;
    }
}

int product(list_t list){
    if (list_isEmpty(list)){
        return 1;
    }
    else
    {
        return list_first(list) * product(list_rest(list));
    }
}

int accumulate(list_t list, int (*fn)(int, int), int base){
    if (list_isEmpty(list)){
        return base;
    }
    else
    {
        return fn(list_first(list), accumulate(list_rest(list), fn, base));
    }
}

static int list_last(list_t list){
// REQUIRES: "list" is not empty
// EFFECTS: returns the last element of list
    if (size(list)==1){
        return list_first(list);
    }
    else
    {
        return list_last(list_rest(list));
    }
}

static list_t list_lrest(list_t list){
// REQUIRES: "list" is no empty
// EFFECTS: returns the list containing all but the last element
    if (size(list) == 1){
        return list_make();
    }
    else
    {
        return list_make(list_first(list), list_lrest(list_rest(list)));
    }
}

list_t reverse(list_t list){
    if (list_isEmpty(list)){
        return list;
    }
    else
    {
        return list_make(list_last(list), reverse(list_lrest(list)));
    }
}

list_t append(list_t first, list_t second){
    if (list_isEmpty(first)){
        return second;
    }
    else
    {
        return append(list_lrest(first), list_make(list_last(first), second));
    }
}

list_t filter_odd(list_t list){
    if (list_isEmpty(list)){
        return list;
    }
    else
    {
        if (list_first(list) % 2 == 1){
            return list_make(list_first(list), filter_odd(list_rest(list)));
        }
        else
        {
            return filter_odd(list_rest(list));
        }
    }
}

list_t filter_even(list_t list){
    if (list_isEmpty(list)){
        return list;
    }
    else
    {
        if (list_first(list) % 2 == 0){
            return list_make(list_first(list), filter_even(list_rest(list)));
        }
        else
        {
            return filter_even(list_rest(list));
        }
    }
}

list_t filter(list_t list, bool (*fn)(int)){
    if (list_isEmpty(list)){
        return list;
    }
    else if (fn(list_first(list)))
    {
        return list_make(list_first(list), filter(list_rest(list), fn));
    }
    else
    {
        return filter(list_rest(list), fn);
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n){
    if (n == 0){
        return append(second, first);
    }
    else
    {
        return list_make(list_first(first), insert_list(list_rest(first), second, n - 1));
    }   
}

list_t chop(list_t list, unsigned int n){
    if (n == 0){
        return list;
    }
    else
    {
        return chop(list_lrest(list), n - 1);
    }
}

int tree_sum(tree_t tree){
    if (tree_isEmpty(tree)){
        return 0;
    }
    else
    {
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}

bool tree_search(tree_t tree, int key){
    if (tree_isEmpty(tree)){
        return false;
    }
    else
    {
        if (tree_elt(tree) == key){
            return true;
        }
        else
        {
            return (tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key));
        }
    }
}

static int min(int a, int b){
//EFFECTS: return the smaller one of two integers
    return ((a < b) ? a : b);
}

static int max(int a, int b){
//EFFECTS: return the greater one of two integers 
    return ((a > b) ? a : b);
}

int depth(tree_t tree){
    if (tree_isEmpty(tree)){
        return 0;
    }
    else
    {
        return 1 + max(depth(tree_left(tree)), depth(tree_right(tree)));
    }
}

int tree_min(tree_t tree){
    if (tree_isEmpty(tree_left(tree))){
        if (tree_isEmpty(tree_right(tree))){
            return tree_elt(tree);
        }
        else
        {
            return min(tree_elt(tree), tree_min(tree_right(tree)));
        }
    }
    else
    {
        if (tree_isEmpty(tree_right(tree))){
            return min(tree_elt(tree), tree_min(tree_left(tree)));
        }
        else
        {
            return min(tree_min(tree_left(tree)), min(tree_elt(tree), tree_min(tree_right(tree))));
        }
    }
}

list_t traversal(tree_t tree){
    if (tree_isEmpty(tree)){
        return list_make();
    }
    else
    {
        return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
    }
}

static bool my_tree_hasPathSum(tree_t tree, int sum, int times){
//EFFECTS: be able to distinguish the tree emptied by recursion and the input empty trees
    if (tree_isEmpty(tree) && sum == 0){
        if (times == 0){
            return false;
        }
        //in case that the input is an empty tree, which doesn't have roof-to-leaf path
        else
        {
            return true;
        }
    }
    else if (tree_isEmpty(tree) || sum == 0){
        return false;
    }
    else
    {
        int newsum = sum - tree_elt(tree);
        return (my_tree_hasPathSum(tree_right(tree), newsum, times + 1)
                || my_tree_hasPathSum(tree_left(tree), newsum, times + 1));
    }
}

bool tree_hasPathSum(tree_t tree, int sum){
    return my_tree_hasPathSum(tree, sum, 0);
}

bool covered_by(tree_t A, tree_t B){
    if (tree_isEmpty(A)){
        return true;
    }
    //An empty is covered by all trees
    else
    {
        if (tree_isEmpty(B)){
            return false;
        }
        //Empty tree covers only other empty trees
        else if (tree_elt(A) == tree_elt(B)){
            return (covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B)));
        }
        else
        {
            return false;
        }
    }
}

bool contained_by(tree_t A, tree_t B){
    if (depth(A) > depth(B)){
        return false;
    }
    else if (covered_by(A, B)){
        return true;
    }
    else
    {
        return (contained_by(A, tree_left(B)) || contained_by(A, tree_right(B)));
    }
}

tree_t insert_tree(int elt, tree_t tree){
    if (tree_isEmpty(tree)){
        return tree_make(elt, tree_make(), tree_make());
    }
    else if (elt < tree_elt(tree))
    {
        return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
    }
    else
    {
        return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
    }
}
