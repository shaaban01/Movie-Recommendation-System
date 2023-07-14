#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>
#include "userController.h"
#include "movieController.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    UserController userController;
    MovieController movieController;
    RatingController ratingController;

    PopularityBasedStrategy strategyPopular;
    ContentBasedFiltering strategyContentBased;
    // UserBasedCollaborativeFiltering strategyUserBased;

    engine.rootContext()->setContextProperty("userController", &userController);
    engine.rootContext()->setContextProperty("ratingController", &ratingController);
    engine.rootContext()->setContextProperty("movieController", &movieController);

    RecommendationEngine recommendationEnginePopularity(&strategyPopular);
    RecommendationEngine recommendationEngineContentBased(&strategyContentBased);
    // RecommendationEngine recommendationEngineUserBased(&strategyUserBased);

    engine.rootContext()->setContextProperty("recommendationEnginePopularity", &recommendationEnginePopularity);
    engine.rootContext()->setContextProperty("recommendationEngineContentBased", &recommendationEngineContentBased);
    // engine.rootContext()->setContextProperty("recommendationEngineUserBased", &recommendationEngineUserBased);

    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
