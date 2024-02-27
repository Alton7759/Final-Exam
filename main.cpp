#include <algorithm>                                                                                      // shuffle(), find(), find_if()
#include <chrono>                                                                                         // steady_clock, duration
#include <concepts>                                                                                       // convertible_to
#include <cstddef>                                                                                        // size_t
#include <forward_list>                                                                                   // Singly linked list
#include <iostream>                                                                                       // standard i/o streams cout, clog, cin
#include <iterator>                                                                                       // next(), istream_iterator
#include <list>                                                                                           // doubly linked list
#include <map>                                                                                            // Binary search tree associative container with no duplicates
#include <random>                                                                                         // random_device, default_random_engine
#include <sstream>                                                                                        // ostringstream
#include <string>                                                                                         // Unbounded strings
#include <unordered_map>                                                                                  // Hash Table associative container with no duplicates
#include <vector>                                                                                         // Unbounded vector

#include "Operations.hpp"
#include "SomeObject.hpp"                                                                                 // Data structures will be filled with some random object, presumably from past homework assignments
#include "Timer.hpp"










/*********************************************************************************************************************************
**  Private type declarations, function declarations, and object definitions
*********************************************************************************************************************************/
namespace    // unnamed, anonymous namespace
{
  /*********************************************************************************************************************************
  **  Type Definitions
  *********************************************************************************************************************************/
  // Preferred clock
  using Clock = std::chrono::steady_clock;

  // Create a matrix indexed by Data Structure and Operation that holds a collection of time samples collected to perform the operation.
  using OperationName     = std::string;
  using DataStructureName = std::string;
  using SnapshotInterval  = std::size_t;
  using ElapsedTime       = Clock::duration;

  // A 3 dimensional collection of elapsed time measurements indexed by interval, data structure, and operation
  using TimeMatrix = std::map<SnapshotInterval, std::map<DataStructureName, std::map<OperationName, ElapsedTime>>>;

  struct Direction
  { enum value {Grow=1, Shrink=-Grow}; };

  using Utilities::Timer;


  template<typename Iter, typename T = typename Iter::value_type>
  struct SampleData : std::vector<T>
  {
    using std::vector<T>::vector;                                                                         // inherit constructors
    SampleData( Iter begin, Iter end ) : std::vector<T>{ begin, end }
    {
      this->shrink_to_fit();
      std::shuffle( this->begin(), this->end(), std::default_random_engine( std::random_device{}() ) );   // Guarantee they are not in any particular order
    }
  };


  /*********************************************************************************************************************************
  **  Function Declarations
  *********************************************************************************************************************************/
  std::ostream & operator<<( std::ostream & stream, const TimeMatrix & matrix );

  template<class Operation>
  void measure( const std::string & structureName,                                                        // free text name of data structure being measured
                const std::string & operationDescription,                                                 // free text name of the operation of the data structure being measured
                Operation           operation,                                                            // operation to be measured, expressed as a Functiod
                Direction::value    direction = Direction::Grow );                                        // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)


  template<class Operation, class Preamble>
  void measure( const std::string & structureName,                                                        // free text name of data structure being measured
                const std::string & operationDescription,                                                 // free text name of the operation of the data structure being measured
                Preamble            preamble,                                                             // setup work to occur before operation, expressed as a Functiod
                Operation           operation,                                                            // operation to be measured, expressed as a Functiod
                Direction::value    direction = Direction::Grow );                                        // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)



  /*********************************************************************************************************************************
  **  Object Definitions
  *********************************************************************************************************************************/
  TimeMatrix        runTimes;                                                                             // collection of operation time measurements
  const SampleData  sampleData{ std::istream_iterator<SomeObject>( std::cin ),                            // define and initialize from standard input a
                                std::istream_iterator<SomeObject>(          ) };                          // collection of data samples
}    // unnamed, anonymous namespace










/***********************************************************************************************************************************
**  main() - Program entry point
***********************************************************************************************************************************/
int main()
{
  Timer totalElapsedTime{ "Timer:  total elapsed time is ", std::clog };

  /*********************************************************************************************************************************
  **  Collect Vector Measurements
  *********************************************************************************************************************************/
  {
    std::clog << "\n\n\nStarting to collect Vector measurements\n";
    Timer timer{ "Timer:  Vector measurements completed in ", std::clog };

    {    // Insert at the back of a vector
      std::vector<SomeObject> v;
      measure( "Vector", "Insert at the back", insert_at_back_of_vector{ v } );
    }


    {    // Insert at the front of a vector
      std::vector<SomeObject> v;
      measure( "Vector", "Insert at the front", insert_at_front_of_vector{ v } );
    }


    {    // Remove from the back of a vector
      std::vector<SomeObject> v{ sampleData.cbegin(), sampleData.cend() };
      measure( "Vector", "Remove from the back", remove_from_back_of_vector{ v }, Direction::Shrink );
    }


    {    // Remove from the front of a vector
      std::vector<SomeObject> v{ sampleData.cbegin(), sampleData.cend() };
      measure( "Vector", "Remove from the front", remove_from_front_of_vector{ v }, Direction::Shrink );
    }


    {    // Search for an element in a vector
      std::vector<SomeObject> v;
      v.reserve( sampleData.size() );
      measure(
          "Vector",
          "Search",
          [&]( const SomeObject & someObject ) { v.push_back( someObject ); },
          search_within_vector{ v, "non-existent" } );
    }
  }    // Collect Vector Measurements





  /*********************************************************************************************************************************
  **  Collect Doubly Linked List Measurements
  *********************************************************************************************************************************/
  {
    std::clog << "\nStarting to collect Doubly Linked List measurements\n";
    Timer timer{ "Timer:  Doubly Linked List measurements completed in ", std::clog };

    {    // Insert at the back of a doubly linked list
      std::list<SomeObject> dll;
      measure( "DLL", "Insert at the back", insert_at_back_of_dll{ dll } );
    }


    {    // Insert at the front of a doubly linked list
      std::list<SomeObject> dll;
      measure( "DLL", "Insert at the front", insert_at_front_of_dll{ dll } );
    }


    {    // Remove from the back of a doubly linked list
      std::list<SomeObject> dll{ sampleData.cbegin(), sampleData.cend() };
      measure( "DLL", "Remove from the back", remove_from_back_of_dll{ dll }, Direction::Shrink );
    }


    {    // Remove from the front of a doubly linked list
      std::list<SomeObject> dll{ sampleData.cbegin(), sampleData.cend() };
      measure( "DLL", "Remove from the front", remove_from_front_of_dll{ dll }, Direction::Shrink );
    }


    {    // Search for an element in a doubly linked list
      std::list<SomeObject> dll;
      measure(
          "DLL",
          "Search",
          [&]( const SomeObject & someObject ) { dll.push_back( someObject ); },
          search_within_dll{ dll, "non-existent" } );
    }
  }    // Collect Doubly Linked List Measurements





  /*********************************************************************************************************************************
  **  Collect Singly Linked List Measurements
  *********************************************************************************************************************************/
  {
    std::clog << "\nStarting to collect Singly Linked List measurements\n";
    Timer timer{ "Timer:  Singly Linked List measurements completed in ", std::clog };

    {    // Insert at the back of a singly linked list
      std::forward_list<SomeObject> sll;
      measure( "SLL", "Insert at the back", insert_at_back_of_sll{ sll } );
    }


    {    // Insert at the front of a singly linked list
      std::forward_list<SomeObject> sll;
      measure( "SLL", "Insert at the front", insert_at_front_of_sll{ sll } );
    }


    {    // Remove from the back of a singly linked list
      std::forward_list<SomeObject> ssl{ sampleData.cbegin(), sampleData.cend() };
      measure( "SLL", "Remove from the back", remove_from_back_of_sll{ ssl }, Direction::Shrink );
    }


    {    // Remove from the front of a singly linked list
      std::forward_list<SomeObject> sll{ sampleData.cbegin(), sampleData.cend() };
      measure( "SLL", "Remove from the front", remove_from_front_of_sll{ sll }, Direction::Shrink );
    }


    {    // Search for an element in a singly linked list
      std::forward_list<SomeObject> sll;
      measure(
          "SLL",
          "Search",
          [&]( const SomeObject & someObject ) { sll.push_front( someObject ); },
          search_within_sll{ sll, "non-existent" } );
    }
  }    // Collect Singly Linked List Measurements





  /*********************************************************************************************************************************
  **  Collect Binary Search Tree Measurements
  *********************************************************************************************************************************/
  {
    std::clog << "\nStarting to collect Binary Search Tree measurements\n";
    Timer timer{ "Timer:  Binary Search Tree measurements completed in ", std::clog };

    {    // Insert into a binary search tree
      std::map<std::string, SomeObject> map;
      measure( "BST", "Insert", insert_into_bst{ map } );
    }


    {    // Remove from a binary search tree
      std::map<std::string, SomeObject> map;
      for( const auto & someObject : sampleData ) map.emplace( someObject.key(), someObject );
      measure( "BST", "Remove", remove_from_bst{ map }, Direction::Shrink );
    }


    {    // Search for an element in a binary search tree
      std::map<std::string, SomeObject> map;
      measure(
          "BST",
          "Search",
          [&]( const SomeObject & someObject ) { map.emplace( someObject.key(), someObject ); },
          search_within_bst{ map, "non-existent" } );
    }
  }    // Collect Binary Search Tree Measurements





  /*********************************************************************************************************************************
  **  Collect Hash Table Measurements
  *********************************************************************************************************************************/
  {
    std::clog << "\nStarting to collect Hash Table measurements\n";
    Timer timer{ "Timer:  Hash Table measurements completed in ", std::clog };

    {    // Insert into a hash table
      std::unordered_map<std::string, SomeObject> u_map;
      measure( "Hash Table", "Insert", insert_into_hash_table{ u_map } );
    }


    {    // Remove from a hash table
      std::unordered_map<std::string, SomeObject> u_map;
      for( const auto & someObject : sampleData ) u_map.emplace( someObject.key(), someObject );
      measure( "Hash Table", "Remove", remove_from_hash_table{ u_map }, Direction::Shrink );
    }


    {    // Search for an element in a hash table
      std::unordered_map<std::string, SomeObject> u_map;
      measure(
          "Hash Table",
          "Search",
          [&]( const SomeObject & someObject ) { u_map.emplace( someObject.key(), someObject ); },
          search_within_hash_table{ u_map, "non-existent" } );
    }
  }    // Collect Hash Table Measurements





  //  Report measurements
  std::cout << runTimes << '\n';

  std::clog << '\n'
            << std::string( 80, '-' ) << '\n';
}  // main()










/*********************************************************************************************************************************
**  Private definitions
*********************************************************************************************************************************/
namespace    // unnamed, anonymous namespace
{
  template<typename T, typename S>
  concept returns_a_value = requires( T t )
  {
    { t( S{} ) } -> std::convertible_to<S const *>;
  };





  template<class Operation>
  void measure( const std::string & structureName,                                                        // free text name of data structure being measured
                const std::string & operationDescription,                                                 // free text name of the operation of the data structure being measured
                Operation           operation,                                                            // operation to be measured, expressed as a Functiod
                Direction::value    direction )                                                           // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)
  {
    static auto noop = []( auto & ) {};                                                                   // A no-operation (do nothing) Functiod. Useful when requesting no setup be done prior to measuring an operation.
    measure( structureName, operationDescription, noop, operation, direction );
  }





  // Template function to measure the elapsed time consumed to perform a container's operation
  template<class Operation, class Preamble>
  void measure( const std::string & structureName,                                                        // free text name of data structure being measured
                const std::string & operationDescription,                                                 // free text name of the operation of the data structure being measured
                Preamble            preamble,                                                             // setup work to occur before operation, expressed as a Functiod defaulted to "do nothing"
                Operation           operation,                                                            // operation to be measured, expressed as a Functiod
                Direction::value    direction )                                                           // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)
  {
    struct progressRAII
    {
      progressRAII( const std::string & structureName, const std::string & operationDescription )
      { std::clog << "  starting " << structureName << "'s " << operationDescription << " operation ... "; }

      ~progressRAII()
      { std::clog << "finished"; }

      Timer duration{ " in ", std::clog };
    } progress_raii{structureName, operationDescription};



    constexpr std::size_t SAMPLE_SIZE = 250;                                                              // Number of operations to perform before reporting timing data

    std::size_t sampleIndex = (direction == Direction::Grow) ? 0 : sampleData.size();
    for( const auto & element : sampleData )
    {
      preamble( element );                                                                                // perform any setup work, but don't include this in the measured time

      // ToDo:  help prevent interruptions, perhaps with "critical section" or "Priority Boost"
      // ToDo:  Remove the function call overhead from the measurement, perhaps with some template or polymorphic std::variant magic
      Clock::time_point start_time;
      Clock::time_point stop_time;

      // Some compilers/linkers (MSVC++) are smart enough to optimize away the searches - there are no side effects and the results
      // is not used.  Others (g++ and clang++) are not. So, some added code was artificially introduced, outside the measured
      // operation of course, to use the results of the search hence preventing it of being optimized away.
      if constexpr( returns_a_value< Operation, SomeObject > )
      {
        start_time = Clock::now();
        auto p = operation( element );
        stop_time  = Clock::now();

        // now pretend to use the results
        std::ostringstream s;
        s << p;   // Assumes "p" has an operator<<
      }
      else
      {
        start_time = Clock::now();
        operation( element );                                                                             // perform the operation and measure the elapsed wall clock time, subject to the OS's task scheduling
        stop_time = Clock::now();
      }

      //if( sampleIndex % SAMPLE_SIZE  ==  0)                                                             // uncomment if you want single samples, otherwise it accumulates all the samples over the interval
      runTimes[( ( sampleIndex / SAMPLE_SIZE ) + 1 ) * SAMPLE_SIZE][structureName][operationDescription] += stop_time - start_time;
      sampleIndex += direction;
    }
  }





  std::ostream & operator<<( std::ostream & stream, const TimeMatrix & matrix )
  {
    if( !matrix.empty() )
    {
      // dump the data collected in a tab-separated values (tsv) table, for example:
      //   Size  Vector/insert  Vector/Remove  List/insert  List/remove
      //   10    1              1              23           14
      //   20    3              2              40           37

      // Display the table header
      stream << "Size";
      for( const auto & [structure, operations] : matrix.begin()->second ) for( const auto & [operation, accumulatedTime] : operations )
      {
        stream << ',' << structure << '/' << operation;
      }
      stream << '\n';

      // Display the table data
      for( const auto & [size, structures] : matrix )
      {
        stream << size;
        for( const auto & [structure, operations] : structures )  for( const auto & [operation, accumulatedTime] : operations )
        {
          stream << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>( accumulatedTime ).count();
        }
        stream << '\n';
      }
    }

    return stream;
  }
}    // namespace
