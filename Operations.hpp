#pragma once
#include <algorithm>
#include <forward_list>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "SomeObject.hpp"









/***********************************************************************************************************************************
**  Insert operations
***********************************************************************************************************************************/
struct insert_at_back_of_vector
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the back of a vector, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// Write the lines of code to insert "object" at the back of "my_vector"
    my_vector.push_back(std::move(object));
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct insert_at_back_of_dll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the back of a doubly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (2) //////////////////////////////
      /// Write the lines of code to insert "object" at the back of "my_dll"
    my_dll.insert(my_dll.end(),std::move(object));
    /////////////////////// END-TO-DO (2) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct insert_at_back_of_sll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the back of a singly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (3) //////////////////////////////
      /// Write the lines of code to insert "object" at the back of "my_sll". Since the SLL has no size() function and no tail pointer, you
      /// must walk the list looking for the last node. Hint:  Do not attempt to insert after "my_sll.end()"
  auto next = my_sll.begin(); 
  auto index = my_sll.before_begin();
  while (next != my_sll.end())
  {
    next++;
    index++;
  }
  my_sll.insert_after(index,std::move(object));
    /////////////////////// END-TO-DO (3) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct insert_at_front_of_vector
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the front of a vector, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (4) //////////////////////////////
      /// Write the lines of code to insert "object" at the front of "my_vector"
    my_vector.insert(my_vector.begin(),std::move(object));
    /////////////////////// END-TO-DO (4) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct insert_at_front_of_dll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the front of a doubly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (5) //////////////////////////////
      /// Write the lines of code to insert "object" at the front of "my_dll"
    my_dll.insert(my_dll.begin(),std::move(object));
    /////////////////////// END-TO-DO (5) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct insert_at_front_of_sll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the front of a singly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (6) //////////////////////////////
      /// Write the lines of code to insert "object" at the front of "my_sll"
      my_sll.insert_after(my_sll.before_begin(),std::move(object));
    /////////////////////// END-TO-DO (6) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct insert_into_bst
{
  // Function takes a constant SomeObject as a parameter, inserts that object indexed by the object's key into a binary search tree, and
  // returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (7) //////////////////////////////
      /// Write the lines of code to insert the object's key and value pair into "my_bst". To obtain the object's key, determine
      /// SomeObject's base type and review your prior homework class interface. For example, if SomeObject's base type is a
      /// HotelReservation, you might obtain the reservation's key with object.reservationNumber().
    my_bst.insert({object.key(),std::move(object)});
    /////////////////////// END-TO-DO (7) ////////////////////////////
  }

  std::map<std::string, SomeObject> & my_bst;                                                                     // binary search tree
};









struct insert_into_hash_table
{
  // Function takes a constant SomeObject as a parameter, inserts that object indexed by the object's key into a hash table, and returns
  // nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (8) //////////////////////////////
      /// Write the lines of code to insert the object's key and value pair into "my_hash_table". To obtain the object's key, determine
      /// SomeObject's base type and review your prior homework class interface. For example, if SomeObject's base type is a
      /// HotelReservation, you might obtain the reservation's key with object.reservationNumber().
    my_hash_table.insert({object.key(),std::move(object)});
    /////////////////////// END-TO-DO (8) ////////////////////////////
  }

  std::unordered_map<std::string, SomeObject> & my_hash_table;                                                    // hash table
};


















/***********************************************************************************************************************************
**  Remove operations
***********************************************************************************************************************************/
struct remove_from_back_of_vector
{
  // Function takes no parameters, removes the object at the back of a vector, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (9) //////////////////////////////
      /// Write the lines of code to remove the object at the back of "my_vector". Remember, attempting to remove an object from an empty
      /// data structure is a logic error.  Include code to avoid that.
    if(!my_vector.empty()) my_vector.pop_back();
    /////////////////////// END-TO-DO (9) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct remove_from_back_of_dll
{
  // Function takes no parameters, removes the object at the back of a doubly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (10) //////////////////////////////
      /// Write the lines of code to remove the object at the back of "my_dll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if(!my_dll.empty()) my_dll.pop_back();
    /////////////////////// END-TO-DO (10) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct remove_from_back_of_sll
{
  // Function takes no parameters, removes the object at the back of a singly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (11) //////////////////////////////
      /// Write the lines of code to remove the object at the back of "my_sll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
  if(my_sll.empty()) return;
  auto next = my_sll.begin(); 
  auto index = my_sll.before_begin();
  auto prev = my_sll.before_begin();
  next++;
  index++;
  unsigned count = 1;
  while (next != my_sll.end())
  {
    prev++;
    next++;
    index++;
    count++;
  }
  if(count > 0) my_sll.erase_after(prev);
    /////////////////////// END-TO-DO (11) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct remove_from_front_of_vector
{
  // Function takes no parameters, removes the object at the front of a vector, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (12) //////////////////////////////
      /// Write the lines of code to remove the object at the front of "my_vector". Remember, attempting to remove an object from an empty
      /// data structure is a logic error.  Include code to avoid that.
    if(!my_vector.empty())my_vector.erase(my_vector.begin());
    /////////////////////// END-TO-DO (12) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct remove_from_front_of_dll
{
  // Function takes no parameters, removes the object at the front of a doubly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (13) //////////////////////////////
      /// Write the lines of code to remove the object at the front of "my_dll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if(!my_dll.empty())my_dll.erase(my_dll.begin());
    /////////////////////// END-TO-DO (13) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct remove_from_front_of_sll
{
  // Function takes no parameters, removes the object at the front of a singly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (14) //////////////////////////////
      /// Write the lines of code to remove the object at the front of "my_sll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if(!my_sll.empty())my_sll.erase_after(my_sll.before_begin());
    /////////////////////// END-TO-DO (14) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct remove_from_bst
{
  // Function takes a constant SomeObject as a parameter, finds and removes from the binary search tree the object with a matching key, and
  // returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (15) //////////////////////////////
      /// Write the lines of code to remove the object from "my_bst" that has a matching key. Remember, attempting to remove an object from
      /// an empty data structure is a logic error.  Include code to avoid that.
    if(!my_bst.empty())my_bst.erase(object.key());
    /////////////////////// END-TO-DO (15) ////////////////////////////
  }

  std::map<std::string, SomeObject> & my_bst;                                                                     // binary search tree
};









struct remove_from_hash_table
{
  // Function takes a constant SomeObject as a parameter, finds and removes from the hash table the object with a matching key, and returns
  // nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (16) //////////////////////////////
      /// Write the lines of code to remove the object from "my_hash_table" that has a matching key. Remember, attempting to remove an
      /// object from an empty data structure is a logic error.  Include code to avoid that.
    if(!my_hash_table.empty())my_hash_table.erase(object.key());
    /////////////////////// END-TO-DO (16) ////////////////////////////
  }

  std::unordered_map<std::string, SomeObject> & my_hash_table;                                                    // hash table
};















/***********************************************************************************************************************************
**  Search operations
***********************************************************************************************************************************/
struct search_within_vector
{
  // Function takes no parameters, searches a vector for an object with a key matching the target key, and returns a pointer to that found
  // object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (17) //////////////////////////////
      /// Write the lines of code to search for the object within "my_vector" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    for(auto & looplook : my_vector) if (looplook.key() == target_key) return &looplook;
      return nullptr;
    /////////////////////// END-TO-DO (17) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
  const std::string         target_key;
};









struct search_within_dll
{
  // Function takes no parameters, searches a doubly linked list for an object with a key matching the target key, and returns a pointer to
  // that found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (18) //////////////////////////////
      /// Write the lines of code to search for the object within "my_dll" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    for (auto & look : my_dll) if (look.key() == target_key) return &look;
    return nullptr;
    /////////////////////// END-TO-DO (18) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
  const std::string       target_key;
};









struct search_within_sll
{
  // Function takes no parameters, searches a singly linked list for an object with a key matching the target key, and returns a pointer to
  // that found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (19) //////////////////////////////
      /// Write the lines of code to search for the object within "my_sll" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
 for (auto & object : my_sll) if (object.key() == target_key) return &object;
    return nullptr;

    /////////////////////// END-TO-DO (19) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
  const std::string               target_key;
};









struct search_within_bst
{
  // Function takes no parameters, searches a binary search tree for an object with a key matching the target key, and returns a pointer to
  // that found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (20) //////////////////////////////
      /// Write the lines of code to search for the object within "my_bst" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    if(auto look = my_bst.find(target_key); look != my_bst.end()) return &look->second;
    return nullptr;
    /////////////////////// END-TO-DO (20) ////////////////////////////
  }

  std::map<std::string, SomeObject> & my_bst;                                                                     // binary search tree
  const std::string                   target_key;
};









struct search_within_hash_table
{
  // Function takes no parameters, searches a hash table for an object with a key matching the target key, and returns a pointer to that
  // found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (21) //////////////////////////////
      /// Write the lines of code to search for the object within "my_hash_table" with a key matching "target_key".  Return a pointer to
      /// that object immediately upon finding it, or a null pointer when you know the object is not in the container.
    if(auto look = my_hash_table.find(target_key); look != my_hash_table.end()) return &look->second;
    return nullptr;
    /////////////////////// END-TO-DO (21) ////////////////////////////
  }

  std::unordered_map<std::string, SomeObject> & my_hash_table;                                                    // hash table
  const std::string                             target_key;
};
