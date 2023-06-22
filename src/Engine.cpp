class RecommendationStrategy
{
public:
    virtual ~RecommendationStrategy() {}
    virtual void recommend() = 0;
};

class UserBasedCollaborativeFiltering : public RecommendationStrategy
{
public:
    void recommend() override
    {
        // UBCF recommendation logic
    }
};

class PopularityBasedStrategy : public RecommendationStrategy
{
public:
    void recommend() override
    {
        // PBS recommendation logic
    }
};

class RecommendationEngine
{
private:
    std::unique_ptr<RecommendationStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<RecommendationStrategy> strategy)
    {
        this->strategy = std::move(strategy);
    }

    void recommend()
    {
        // Delegate the call to the strategy object
        strategy->recommend();
    }
};
