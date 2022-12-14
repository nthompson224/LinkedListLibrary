Author: Nate Thompson
        10/21/2022

Templatized Linked List Library:

    Linked list library with safe memory freeing, copy constructor and operator overloads

    Member Functions:

        int size() => returns the size of the linked list 
                        (acts like an array so size will be #-of-elements + 1)

        bool isEmpty() => returns if the list is empty or not

        void append(T) => appends to the end of the list

        void insert(int, T) => inserts element at given index

        void erase(int) => erases element at given index

        void sort(bool) => sorts the linked list using merge sort
                                bool is defaulted to true to sort least->greatest
                                if passed as false to sort greatest->least

        int find(T) => searches through the array and returns index of passed val
                            returns -1 if val not found

        void reverse() => reverses the list

    Overloads:

        operator[](int) => returns the ListNode at the given index

        operator=(const LinkedList&) => copies the contents of the parameter
                                            linked list to the list on the
                                                lhs list; returns lhs list

        operator+(const LinkedList&) => Concatenates the contents of the parameter
                                            linked list onto the end of the
                                                lhs list; returns new list

        operator+(T) => Creates a new node initialized with value and appends it 
                            to the end of the list; returns a new list

        operator+=(const LinkedList&) => appends the parameter list to the end
                                            of the lhs list; returns the lhs list

        operator+=(T) => Creates a new node initialized with value and appends it 
                            to the end of the list; returns lhs list

        operator<< => overload to easiy print the contents of the list
                        prints: "[1, 2, 3]"
