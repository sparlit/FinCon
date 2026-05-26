#include <QtTest>
#include "core/DataHub.h"
#include "core/Result.h"
#include "nodes/WorkflowValidator.h"

class FinConSystemTests : public QObject {
    Q_OBJECT
private slots:
    void testDataHubPubSub() {
        bool received = false;
        FinConCore::FinConDataHub::instance().subscribe("test/topic", this, [&](const QJsonDocument& data) {
            received = true;
        });

        QJsonObject obj;
        obj["price"] = 100;
        FinConCore::FinConDataHub::instance().publish("test/topic", QJsonDocument(obj));

        QVERIFY(received);
    }

    void testWorkflowValidator() {
        std::map<std::string, nodes::Node> graph;
        graph["A"] = {"A", {"B"}};
        graph["B"] = {"B", {"C"}};
        graph["C"] = {"C", {"A"}}; // Cycle

        QVERIFY(nodes::WorkflowValidator::hasCycle(graph) == true);

        graph["C"] = {"C", {}}; // Break cycle
        QVERIFY(nodes::WorkflowValidator::hasCycle(graph) == false);
    }

    void testResult() {
        FinConCore::FinConResult<int> res(42);
        QVERIFY(res.has_value());
        QCOMPARE(res.value(), 42);

        FinConCore::FinConResult<int> err(std::string("failed"));
        QVERIFY(!err.has_value());
        QCOMPARE(err.error(), std::string("failed"));
    }
};

QTEST_MAIN(FinConSystemTests)
#include "FinConSystemTests.moc"
