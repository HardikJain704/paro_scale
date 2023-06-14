#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <random>

std::mutex mtx; 

std::queue<int> sharedQueue; 

const int NUM_PRODUCERS = 2; 
const int NUM_VALUES_PER_PRODUCER = 5; 


void producerFunction(int producerId)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < NUM_VALUES_PER_PRODUCER; ++i)
    {
        int value = dis(gen);

        
        std::lock_guard<std::mutex> lock(mtx);
        
        sharedQueue.push(value);
        std::cout << "Producer " << producerId << " produced: " << value << std::endl;
    }
}

void consumerFunction()
{
    while (true)
    {
        
        std::lock_guard<std::mutex> lock(mtx);
        
        if (!sharedQueue.empty())
        {
            int value = sharedQueue.front();
            sharedQueue.pop();
            std::cout << "Consumer consumed: " << value << std::endl;
        }

        
    }
}

int main()
{
    std::vector<std::thread> producers;
    std::thread consumer(consumerFunction);

    
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        producers.emplace_back(producerFunction, i + 1);
    }

  
    for (auto& producer : producers)
    {
        producer.join();
    }

    consumer.join();

    return 0;
}