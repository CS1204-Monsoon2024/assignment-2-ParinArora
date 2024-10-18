//TODO: Implement HashTable class with insert, search, delete and printTable functions 
// and also implement the resize function to resize the table when the load factor exceeds 0.8
// The HashTable should be able to handle collisions using quadratic probing.
#include <iostream>
#include <vector>
using namespace std;

// We want our hash table to be able to bucket integers into m buckets with the hash function h(x) = x mod m
// our hash table will be an array with key value pairs where key is the index/bucket and value is the integer

class HashTable{
    private:
        int size; // to keep track of the size of the table/ number of buckets
        int capacity; // to keep track of the number of elements in the table to calculate the load
        int* arr; // the array to store the key value pairs

    public:
        HashTable(int m){
            size = m;
            capacity = 0;
            arr = new int[size];
            for (int i=0; i<size; i++){
                arr[i] = -1;
            }
        }

        // to inset a key we need to find the index using the hash function and handle the case whee the index is already occupied(collision) and use quadratic probing to find the next empty index
        // but first we find the load and see if we need to resize the table
        void insert(int key){
            float load = static_cast<float> (capacity)/size;
            if (load>=0.8){
                resizeTable();
            }
            int index = key%size;
            if (arr[index] == key) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
            }
            if (arr[index]==-1){
                arr[index] = key;
                capacity++;
                return;
            }
            else{
                for (int i=1; i<size; i++){
                    int newIndex = (index + i*i)%size;
                    if (arr[newIndex] == key) {
                    cout << "Duplicate key insertion is not allowed" << endl;
                    return;
                    }
                    if (arr[newIndex]==-1){
                        arr[newIndex] = key;
                        capacity++;
                        return;
                    }
                }
            }
            cout << "Max probing limit reached!" << endl;
        }

        // to remove a key we need to find the index using the hash function and handle the case where the index is already occupied and use quadratic probing to find the key
        void remove(int key){
            int index = key%size;
            if (arr[index]==key){
                arr[index] = -1;
                capacity--;
            }
            else{
                int originalindex = index;
                for (int i=1; (index +i*i)%size !=originalindex; i++){
                    int newIndex = (index + i*i)%size;
                    if (arr[newIndex]==key){
                        arr[newIndex] = -1;
                        capacity--;
                        return;
                    }
                }
            }
            cout << "Element not found" << endl;
        }
        

        // to resize we need to creat a new array of atleast size 2*size and rehash all the elements
        void resizeTable(){
            int newsize = nextPrime(2*size); // we need to find a prime number bigger than 2*size
            int* newarr = new int[newsize];
            for (int i=0; i<newsize; i++){
                newarr[i] = -1;
            }
            for (int i=0; i<size; i++){
                if (arr[i]!=-1){
                    int key = arr[i];
                    int index = key%newsize;
                    if (newarr[index]==-1){
                        newarr[index] = key;
                    }
                    else{
                        for (int j=1; j<newsize; j++){
                            int newIndex = (index + j*j)%newsize;
                            if (newarr[newIndex]==-1){
                                newarr[newIndex] = key;
                                break;
                            }
                        }
                    }
                }
            }
            delete[] arr;
            arr = newarr;
            size = newsize;
        }

        // to search we simply find the index and if the key is not there we use quadratic probing to find the key 
        int search(int key){
            int index = key%size;
            if (arr[index]==key){
                return index;
            }
            else{
                for (int i=1; (index + i*i)%size!=index; i++){
                    int newIndex = (index + i*i)%size;
                    if (arr[newIndex] == -1) {
                        return -1;
                    }
                    if (arr[newIndex] == key) {
                        return newIndex;
                    }
                    
                }
            }
            return -1;
        }


        //print according to the readme file
        void printTable(){
            for (int i=0; i<size; i++){
                if (arr[i]==-1){
                    cout << "- " ;
                }
                else{
                    cout << arr[i] << " " ;
                }
            }
            cout << endl;
        }


        // we need to find a prime number bigger than 2*crrent size to resize the table
        // so we implement helper functions to help us find a prime
        bool isPrime(int num) {
            if (num <= 1) return false;
            if (num == 2 || num == 3) return true;
            if (num % 2 == 0 || num % 3 == 0) return false;
            for (int i = 5; i * i <= num; i += 6) {
                if (num % i == 0 || num % (i + 2) == 0) return false;
            }
            return true;
        }

        int nextPrime(int n) {
            int primeCandidate = n;
            while (!isPrime(primeCandidate)) {
                primeCandidate++;
            }
            return primeCandidate;
        }
};