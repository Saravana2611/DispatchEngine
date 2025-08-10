
const int BUFFER_SIZE = 100;

class Worker
{
    public:
        Worker();
        void registerAsWorker();
    
    private:
        std::string uid_;
};