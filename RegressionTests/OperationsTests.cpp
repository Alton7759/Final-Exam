#include <concepts>    // same_as
#include <cstddef>     // size_t
#include <exception>
#include <forward_list>
#include <iomanip>     // setprecision
#include <iostream>    // precision(), flags(), endl(), fmtflags, streamsize, boolalpha, showpoint, fixed
#include <iterator>    // distance(), next()
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>    // pair
#include <vector>

#include "SomeObject.hpp"
// #include "CheckResults.hpp"  see below, a couple of operator<< helper functions are needed first
#include "Operations.hpp"



namespace Regression
{
  template <typename T, typename U>
  std::ostream & operator<<( std::ostream & s, const std::pair<T, U> & pair )
  {
    return s << " {" << pair.first << "}, {" << pair.second << "} ";
  }

  template <typename T>
  concept StandardContainer =
           std::same_as<T,  std::vector       <typename T::value_type>>
       ||  std::same_as<T,  std::list         <typename T::value_type>>
       ||  std::same_as<T,  std::forward_list <typename T::value_type>>
       ||  std::same_as<T,  std::map          <typename T::key_type, typename T::mapped_type>>
       ||  std::same_as<T,  std::unordered_map<typename T::key_type, typename T::mapped_type>>;

  template<StandardContainer Structure>
  std::ostream & operator<<( std::ostream & s, const Structure & structure )
  {
    std::size_t size = 0;

    if constexpr( requires { structure.size(); } )  size = structure.size();
    else                                            size = std::distance( structure.begin(), structure.end() );

    s << "\n    Size: " << size << '\n';

    std::size_t i = 0;
    for( auto && e : structure ) s << "    [" << i++ << "]  {" << e << "}\n";

    return s;
  }
}    // namespace Regression

#include "CheckResults.hpp"







namespace    // anonymous
{
  class OperationsRegressionTest
  {
    public:
      OperationsRegressionTest();

    private:
      void validationTests   ();

      const SomeObject b0,                                //     | Key field   |
                       b1{ "parameter 1"                                                },   // dup key with b2
                       b2{ "parameter 1",     "parameter 2"                             },   // dup key with b1
                       b3{ "parameter 1",     "parameter 2",      "parameter 3"         },   // dup key with b4
                       b4{ "parameter 1",     "parameter 2",      "parameter 3", 123.79 },   // dup key with b3
                       b5{ "First Parameter", "Second Parameter", "1-234-567-0", 123.79 };


      Regression::CheckResults affirm;
  } run_verification_tests;



  void OperationsRegressionTest::validationTests()
  {
    /*******************************************************************************************************************************
    **  Vector Operations
    *******************************************************************************************************************************/
    {    // insert at the back of a vector
      std::vector<SomeObject>  v;
      insert_at_back_of_vector insert{ .my_vector = v };

      insert( b1 ), insert( b2 ), insert( b3 );
      affirm.is_equal( "Insert at the back of a vector     ", std::vector{ b1, b2, b3 }, v );
    }


    {    // Insert at the front of a vector
      std::vector<SomeObject>   v;
      insert_at_front_of_vector insert{ .my_vector = v };

      insert( b1 ), insert( b2 ), insert( b3 );
      affirm.is_equal( "Insert at the front of a vector    ", std::vector{ b3, b2, b1 }, v );
    }


    {    // Remove from the back of a vector
      std::vector                v{ b1, b2, b3 };
      remove_from_back_of_vector remove{ .my_vector = v };

      remove( b0 ), affirm.is_equal( "remove from the back of a vector 1 ", std::vector<SomeObject>{ b1, b2 }, v );
      remove( b0 ), affirm.is_equal( "remove from the back of a vector 2 ", std::vector<SomeObject>{ b1     }, v );
      remove( b0 ), affirm.is_equal( "remove from the back of a vector 3 ", std::vector<SomeObject>{        }, v );
      remove( b0 ), affirm.is_equal( "remove from the back of a vector 4 ", std::vector<SomeObject>{        }, v );    // attempts to remove an element from an empty vector
    }


    { // Remove from the front of a vector
      std::vector                 v{ b1, b2, b3 };
      remove_from_front_of_vector remove{ .my_vector = v };

      remove( b0 ), affirm.is_equal( "remove from the front of a vector 1", std::vector<SomeObject>{ b2, b3 }, v );
      remove( b0 ), affirm.is_equal( "remove from the front of a vector 2", std::vector<SomeObject>{ b3     }, v );
      remove( b0 ), affirm.is_equal( "remove from the front of a vector 3", std::vector<SomeObject>{        }, v );
      remove( b0 ), affirm.is_equal( "remove from the front of a vector 4", std::vector<SomeObject>{        }, v );  // attempts to remove an element from an empty vector
    }


    { // Search for an element in a vector
      std::vector          v{ b0, b2, b4, b1, b3 };
      search_within_vector search_1{ .my_vector = v, .target_key = b4.key() };
      search_within_vector search_2{ .my_vector = v, .target_key = "---"    };

      affirm.is_equal( "search within a vector 1           ", &v[2],    search_1( 0 ) );
      affirm.is_equal( "search within a vector 2           ", b4,      *search_1( 0 ) );
      affirm.is_equal( "search within a vector 3           ", nullptr,  search_2( 0 ) );
    }






    /*******************************************************************************************************************************
    **  Doubly Linked List Operations
    *******************************************************************************************************************************/
    {    // insert at the back of a doubly linked list
      std::list<SomeObject> dll;
      insert_at_back_of_dll insert{ .my_dll = dll };

      insert( b1 ), insert( b2 ), insert( b3 );
      affirm.is_equal( "Insert at the back of a DLL        ", std::list{ b1, b2, b3 }, dll );
    }


    {    // insert at the front of a doubly linked list
      std::list<SomeObject>  dll;
      insert_at_front_of_dll insert{ .my_dll = dll };

      insert( b1 ), insert( b2 ), insert( b3 );
      affirm.is_equal( "Insert at the front of a DLL       ", std::list{ b3, b2, b1 }, dll );
    }


    {    // Remove from the back of a doubly linked list
      std::list               dll{ b1, b2, b3 };
      remove_from_back_of_dll remove{ .my_dll = dll };

      remove( b0 ), affirm.is_equal( "remove from the back of a DLL 1    ", std::list<SomeObject>{ b1, b2 }, dll );
      remove( b0 ), affirm.is_equal( "remove from the back of a DLL 2    ", std::list<SomeObject>{ b1     }, dll );
      remove( b0 ), affirm.is_equal( "remove from the back of a DLL 3    ", std::list<SomeObject>{        }, dll );
      remove( b0 ), affirm.is_equal( "remove from the back of a DLL 4    ", std::list<SomeObject>{        }, dll );  // attempts to remove an element from an empty list
    }


    { // Remove from the front of a doubly linked list
      std::list                dll{ b1, b2, b3 };
      remove_from_front_of_dll remove{ .my_dll = dll };

      remove( b0 ), affirm.is_equal( "remove from the front of a DLL 1   ", std::list<SomeObject>{ b2, b3 }, dll );
      remove( b0 ), affirm.is_equal( "remove from the front of a DLL 2   ", std::list<SomeObject>{ b3     }, dll );
      remove( b0 ), affirm.is_equal( "remove from the front of a DLL 3   ", std::list<SomeObject>{        }, dll );
      remove( b0 ), affirm.is_equal( "remove from the front of a DLL 4   ", std::list<SomeObject>{        }, dll );  // attempts to remove an element from an empty list
    }


    { // Search for an element in a doubly linked list
      std::list         dll{ b0, b2, b4, b1, b3 };
      search_within_dll search_1{ .my_dll = dll, .target_key = b4.key() };
      search_within_dll search_2{ .my_dll = dll, .target_key = "---" };

      affirm.is_equal( "search within a DLL 1              ", &*( std::next( dll.begin(), 2 ) ),  search_1( 0 ) );
      affirm.is_equal( "search within a DLL 2              ", b4,                                *search_1( 0 ) );
      affirm.is_equal( "search within a DLL 3              ", nullptr,                            search_2( 0 ) );
    }






    /*******************************************************************************************************************************
    **  Singly Linked List Operations
    *******************************************************************************************************************************/
    { // insert at the back of a singly linked list
      std::forward_list<SomeObject> sll;
      insert_at_back_of_sll         insert{ .my_sll = sll };

      insert( b1 ), insert( b2 ), insert( b3 );
      affirm.is_equal( "Insert at the back of a SLL        ", std::forward_list{ b1, b2, b3 }, sll );
    }


    { // insert at the front of a singly linked list
      std::forward_list<SomeObject> sll;
      insert_at_front_of_sll        insert{ .my_sll = sll };

      insert( b1 ), insert( b2 ), insert( b3 );
      affirm.is_equal( "Insert at the front of a SLL       ", std::forward_list{ b3, b2, b1 }, sll );
    }


    { // Remove from the back of a singly linked list
      std::forward_list       sll{ b1, b2, b3 };
      remove_from_back_of_sll remove{ .my_sll = sll };

      remove( b0 ), affirm.is_equal( "remove from the back of a SLL 1    ", std::forward_list<SomeObject>{ b1, b2 }, sll );
      remove( b0 ), affirm.is_equal( "remove from the back of a SLL 2    ", std::forward_list<SomeObject>{ b1     }, sll );
      remove( b0 ), affirm.is_equal( "remove from the back of a SLL 3    ", std::forward_list<SomeObject>{        }, sll );
      remove( b0 ), affirm.is_equal( "remove from the back of a SLL 4    ", std::forward_list<SomeObject>{        }, sll );  // attempts to remove an element from an empty list
    }


    { // Remove from the front of a singly linked list
      std::forward_list        sll{ b1, b2, b3 };
      remove_from_front_of_sll remove{ .my_sll = sll };

      remove( b0 ), affirm.is_equal( "remove from the front of a SLL 1   ", std::forward_list<SomeObject>{ b2, b3 }, sll );
      remove( b0 ), affirm.is_equal( "remove from the front of a SLL 2   ", std::forward_list<SomeObject>{ b3     }, sll );
      remove( b0 ), affirm.is_equal( "remove from the front of a SLL 3   ", std::forward_list<SomeObject>{        }, sll );
      remove( b0 ), affirm.is_equal( "remove from the front of a SLL 4   ", std::forward_list<SomeObject>{        }, sll );  // attempts to remove an element from an empty list
    }


    { // Search for an element in a singly linked list
      std::forward_list sll{ b0, b2, b4, b1, b3 };
      search_within_sll search_1{ .my_sll = sll, .target_key = b4.key() };
      search_within_sll search_2{ .my_sll = sll, .target_key = "---" };

      affirm.is_equal( "search within a SLL 1              ", &*( std::next( sll.begin(), 2 ) ),  search_1( 0 ) );
      affirm.is_equal( "search within a SLL 2              ", b4,                                *search_1( 0 ) );
      affirm.is_equal( "search within a SLL 3              ", nullptr,                            search_2( 0 ) );
    }






    /*******************************************************************************************************************************
    **  Binary Search Tree Operations
    *******************************************************************************************************************************/
    { // insert into a binary search tree
      std::map<std::string, SomeObject> map;
      insert_into_bst                   insert{ .my_bst = map };

      insert( b1 ), insert( b2 ), insert( b3 ), insert( b5 );
      affirm.is_equal    ( "Insert into a binary search tree 1 ", std::map<std::string, SomeObject>{ { b1.key(), b1 }, { b3.key(), b3 }, { b5.key(), b5 } }, map );  // b1, b2 dup key
      affirm.is_not_equal( "Insert into a binary search tree 2 ", std::map<std::string, SomeObject>{ { b2.key(), b2 }, { b3.key(), b3 }, { b5.key(), b5 } }, map );
      affirm.is_equal    ( "Insert into a binary search tree 3 ", std::map<std::string, SomeObject>{ { b3.key(), b3 }, { b5.key(), b5 }, { b1.key(), b1 } }, map );
    }


    { // remove from a binary search tree
      std::map<std::string, SomeObject> map{ { b1.key(), b1 }, { b3.key(), b3 }, { b5.key(), b5 } };
      remove_from_bst                   remove{ .my_bst = map };

      remove( b3 ), affirm.is_equal( "remove from a binary search tree 1 ", std::map<std::string, SomeObject>{ { b1.key(), b1 }, { b5.key(), b5 } }, map );
      remove( b1 ), affirm.is_equal( "remove from a binary search tree 2 ", std::map<std::string, SomeObject>{ { b5.key(), b5 }                   }, map );
      remove( b5 ), affirm.is_equal( "remove from a binary search tree 3 ", std::map<std::string, SomeObject>{                                    }, map );
      remove( b0 ), affirm.is_equal( "remove from a binary search tree 4 ", std::map<std::string, SomeObject>{                                    }, map );    // attempts to remove an element from an empty tree
    }


    { // Search for an element in a binary search tree
      std::map<std::string, SomeObject> map{ { b1.key(), b1 }, { b3.key(), b3 }, { b5.key(), b5 } };
      search_within_bst                 search_1{ .my_bst = map, .target_key = b3.key() };
      search_within_bst                 search_2{ .my_bst = map, .target_key = "---" };

      affirm.is_equal( "search within a BST 1              ", &( map.at(b3.key()) ),  search_1( 0 ) );
      affirm.is_equal( "search within a BST 2              ", b3,                    *search_1( 0 ) );
      affirm.is_equal( "search within a BST 3              ", nullptr,                search_2( 0 ) );
    }






    /*******************************************************************************************************************************
    **  Hash Table Operations
    *******************************************************************************************************************************/
    { // insert into a hash table
      std::unordered_map<std::string, SomeObject> h_tbl;
      insert_into_hash_table                      insert{ .my_hash_table = h_tbl };

      insert( b1 ), insert( b2 ), insert( b3 ), insert( b5 );
      affirm.is_equal    ( "Insert into a hash table 1         ", std::unordered_map<std::string, SomeObject>{ { b1.key(), b1 }, { b3.key(), b3 }, { b5.key(), b5 } }, h_tbl );  // b1, b2 dup key
      affirm.is_not_equal( "Insert into a hash table 2         ", std::unordered_map<std::string, SomeObject>{ { b2.key(), b2 }, { b3.key(), b3 }, { b5.key(), b5 } }, h_tbl );
      affirm.is_equal    ( "Insert into a hash table 3         ", std::unordered_map<std::string, SomeObject>{ { b3.key(), b3 }, { b5.key(), b5 }, { b1.key(), b1 } }, h_tbl );
    }


    { // remove from a hash table
      std::unordered_map<std::string, SomeObject> h_tbl{ { b1.key(), b1 }, { b3.key(), b3 }, { b5.key(), b5 } };
      remove_from_hash_table                      remove{ .my_hash_table = h_tbl };

      remove( b3 ), affirm.is_equal( "remove from a hash table 1         ", std::unordered_map<std::string, SomeObject>{ { b1.key(), b1 }, { b5.key(), b5 } }, h_tbl );
      remove( b1 ), affirm.is_equal( "remove from a hash table 2         ", std::unordered_map<std::string, SomeObject>{ { b5.key(), b5 }                   }, h_tbl );
      remove( b5 ), affirm.is_equal( "remove from a hash table 3         ", std::unordered_map<std::string, SomeObject>{                                    }, h_tbl );
      remove( b0 ), affirm.is_equal( "remove from a hash table 4         ", std::unordered_map<std::string, SomeObject>{                                    }, h_tbl );    // attempts to remove an element from an empty tree
    }


    { // Search for an element in a hash table
      std::unordered_map<std::string, SomeObject> h_tbl{ { b1.key(), b1 }, { b3.key(), b3 }, { b5.key(), b5 } };
      search_within_hash_table                    search_1{ .my_hash_table = h_tbl, .target_key = b3.key() };
      search_within_hash_table                    search_2{ .my_hash_table = h_tbl, .target_key = "---" };

      affirm.is_equal( "search within a hash table 1       ", &( h_tbl.at( b3.key() ) ),  search_1( 0 ) );
      affirm.is_equal( "search within a hash table 2       ", b3,                        *search_1( 0 ) );
      affirm.is_equal( "search within a hash table 3       ", nullptr,                    search_2( 0 ) );
    }
  } // validationTests()










  OperationsRegressionTest::OperationsRegressionTest()
  {
    struct StreamStateRAII
    {
      ~StreamStateRAII()
      {
        std::clog.precision( precision );
        std::clog.flags    ( flags     );
      }

      std::ios::fmtflags flags     = std::clog.flags();
      std::streamsize    precision = std::clog.precision();
    } stream_state_raii;

    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );
    affirm.policy = Regression::CheckResults::ReportingPolicy::BRIEF;



    try
    {
      std::clog << "\nData Structure Operation Tests\n";
      validationTests();

      std::clog << "\n\n" << affirm << '\n';
    }
    catch( const std::exception & ex )
    {
      std::clog << "FAILURE:  Regression test for \"nData Structure Operations\" failed with an unhandled exception. \n\n\n"
                << ex.what() << std::endl;
    }
  }
}    // namespace
