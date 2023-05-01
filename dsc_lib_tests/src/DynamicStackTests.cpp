#include "catch.hpp"
#include <dsc/DynamicStack.h>
#include <stdio.h>
#include <iostream>

namespace dsc::stack::tests {

struct TestObject {
  TestObject() : X(0)
  {
    m_data = new int[5];
  }
  TestObject(int scalar) : X(scalar)
  {
    m_data = new int[5];
  }
  TestObject(const TestObject& other) = delete;
  //{
  //  X      = other.X;
  //  m_data = new int[5];
  //  for (size_t i = 0; i < 5; ++i)
  //    m_data[i] = other.m_data[i];
  //}
  TestObject(TestObject&& other) : X(other.X)
  {
    m_data       = other.m_data;
    other.m_data = nullptr;
  }
  TestObject& operator=(const TestObject& other)
  {
    X      = other.X;
    m_data = new int[5];
    for (size_t i = 0; i < 5; ++i)
      m_data[i] = other.m_data[i];

    return *this;
  }
  TestObject& operator=(TestObject&& other)
  {
    X            = other.X;
    m_data       = other.m_data;
    other.m_data = nullptr;

    return *this;
  }
  ~TestObject()
  {
    //std::cout << "destructor " << m_data << std::endl;
    delete[] m_data;
  }

  friend std::ostream& operator<<(std::ostream& out, const TestObject& t)
  {
    return out << t.X << " " << t.m_data << "\n";
  }

  int  X;
  int* m_data = nullptr;
};


SCENARIO("testing emplace with TestObject as data")
{
  GIVEN("dynamic stack")
  {
    auto sut = DynamicStack<TestObject>();
  
    WHEN("Emplace one object with data X=1 ") 
    {
      // there is a memory leak when t1 exists
      //TestObject t1;
      sut.Emplace(1);

      THEN("top object should have X=1"){
        REQUIRE(sut.Top().X == 1);
      //  REQUIRE(t1.X == 1);
        REQUIRE_FALSE(sut.Empty());

        AND_THEN("after pop stack should be empty")
        {
          sut.Pop();
          REQUIRE(sut.Empty());
        }
      }
    }
    WHEN("Emplace two objects with data X=1 and X=2") 
    {
      //TestObject t1, t2;
      sut.Emplace(1);
      sut.Emplace(2);

      THEN("top object should have X=2"){
        REQUIRE(sut.Top().X == 2);
        //REQUIRE(t2.X == 2);
        //REQUIRE(t1.X == 1);
        REQUIRE_FALSE(sut.Empty());

        AND_THEN("after pop, top object should have X=1")
        {
          sut.Pop();
          REQUIRE(sut.Top().X == 1);
          REQUIRE_FALSE(sut.Empty());

          AND_THEN("after pop stack should be empty")
          {
            sut.Pop();
            REQUIRE(sut.Empty());
          }
        }
      }
    }
  }
  GIVEN("dynamic stack and generator")
  {
    auto sut = DynamicStack<TestObject>();
    auto range = GENERATE(2,100);

    WHEN("Emplace TestObject " << range << " times")
    {
      for(auto i = 2; i <= range; ++i)
      {
        sut.Emplace(i);
      }

      THEN("top element should have X = " << range)
      {
        REQUIRE(sut.Top().X == range);
        AND_THEN("running while loop until stack is empty should run " << range - 1 << " times")
        {
          int counter = 0;

          while(!sut.Empty())
          {
            REQUIRE(sut.Top().X == range - counter );
            sut.Pop();
            ++counter;
          }
          REQUIRE(counter == range - 1);
          REQUIRE(sut.Empty());
        }
      }
    }
  }
}

SCENARIO("testing Dynamic Stack push and pop on int as data")
{
  GIVEN("dynamic stack")
  {
    auto sut = DynamicStack<int>();
    auto range = GENERATE(2,100);

    WHEN("Push " << range << " times")
    {
      for(auto i = 2; i <= range; ++i)
      {
        sut.Push(i);
      }

      THEN("top element should be " << range)
      {
        REQUIRE(sut.Top() == range);
        AND_THEN("running while loop until stack is empty should run " << range - 1 << " times")
        {
          int counter = 0;

          while(!sut.Empty())
          {
            REQUIRE(sut.Top() == range - counter );
            sut.Pop();
            ++counter;
          }
          REQUIRE(counter == range - 1);
          REQUIRE(sut.Empty());
        }
      }
    }
  }
}

SCENARIO("testing Dynamic Stack push and pop on TestObject as data")
{
  GIVEN("dynamic stack")
  {
    auto sut = DynamicStack<TestObject>();
  
    WHEN("Push one object with data X=1 ") 
    {
      sut.Push(TestObject(1));

      THEN("top object should have X=1"){
        REQUIRE(sut.Top().X == 1);
        REQUIRE_FALSE(sut.Empty());

        AND_THEN("after pop stack should be empty")
        {
          sut.Pop();
          REQUIRE(sut.Empty());
        }
      }
    }
    WHEN("Push two objects with data X=1 and X=2") 
    {
      sut.Push(TestObject(1));
      sut.Push(TestObject(2));

      THEN("top object should have X=2"){
        REQUIRE(sut.Top().X == 2);
        REQUIRE_FALSE(sut.Empty());

        AND_THEN("after pop, top object should have X=1")
        {
          sut.Pop();
          REQUIRE(sut.Top().X == 1);
          REQUIRE_FALSE(sut.Empty());

          AND_THEN("after pop stack should be empty")
          {
            sut.Pop();
            REQUIRE(sut.Empty());
          }
        }
      }
    }
  }
  GIVEN("dynamic stack and generator")
  {
    auto sut = DynamicStack<TestObject>();
    auto range = GENERATE(2,100);

    WHEN("Push TestObject " << range << " times")
    {
      for(auto i = 2; i <= range; ++i)
      {
        sut.Push(TestObject(i));
      }

      THEN("top element should have X = " << range)
      {
        REQUIRE(sut.Top().X == range);
        AND_THEN("running while loop until stack is empty should run " << range - 1 << " times")
        {
          int counter = 0;

          while(!sut.Empty())
          {
            REQUIRE(sut.Top().X == range - counter );
            sut.Pop();
            ++counter;
          }
          REQUIRE(counter == range - 1);
          REQUIRE(sut.Empty());
        }
      }
    }
  }
}

SCENARIO("testing Dynamic Stack push and pop on TestObject pointers as data")
{
  GIVEN("dynamic stack of TestObject pointers and three TestObject pointers to objects")
  {
    auto sut = DynamicStack<TestObject*>();
    TestObject* t1 = new TestObject(10);
    TestObject* t2 = new TestObject(20);
    TestObject* t3 = new TestObject(30);

    WHEN("Push t1 and change X of t1")
    {
      sut.Push(t1);
      t1->X = t1->X/10;
      
      THEN("top element should be t1 with 1 as X") { 
        REQUIRE(sut.Top()->X == 1);
        AND_THEN("after Pop stack should be empty")
        {
          sut.Pop();
          REQUIRE(sut.Empty());
        }
      }
    }

    WHEN("Push t1 and t2 and change X of t1 and t2")
    {
      sut.Push(t1);
      sut.Push(t2);
      t1->X = t1->X/10;
      t2->X = t2->X/10;

      THEN("top element should be t2 with 2 as X") { 
        REQUIRE(sut.Top()->X == 2);
        AND_THEN("after Pop top element should be t1 with 1 as X")
        {
          sut.Pop();
          REQUIRE(sut.Top()->X == 1);
          AND_THEN("after Pop stack should be empty")
          {
            sut.Pop();
            REQUIRE(sut.Empty());
          }
        }
      }
    }

    WHEN("Push t1, t2 and t3 and change X of t1, t2 and t3")
    {
      sut.Push(t1);
      sut.Push(t2);
      sut.Push(t3);
      t1->X = t1->X/10;
      t2->X = t2->X/10;
      t3->X = t3->X/10;

      THEN("top element should be t3 with 3 as X") { 
        REQUIRE(sut.Top()->X == 3);
        AND_THEN("after Pop top element should be t2 with 2 as X")
        {
          sut.Pop();
          REQUIRE(sut.Top()->X == 2);
          AND_THEN("after Pop top element should be t1 with 1 as X")
          {
            sut.Pop();
            REQUIRE(sut.Top()->X == 1);
            AND_THEN("after Pop stack should be empty")
            {
              sut.Pop();
              REQUIRE(sut.Empty());
            }
          }
        }
      }
    }

    delete t1;
    delete t2;
    delete t3;
  }
}

} // namespace dsc::stack::tests
