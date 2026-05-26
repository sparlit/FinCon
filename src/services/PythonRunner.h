#pragma once
#include <QObject>
#include <QProcess>
#include <QQueue>
#include <functional>

namespace services {

struct PythonJob {
    QString script;
    QStringList args;
    std::function<void(QString)> onOutput;
    std::function<void(int)> onFinished;
};

class PythonRunner : public QObject {
    Q_OBJECT
public:
    static PythonRunner& instance() {
        static PythonRunner inst;
        return inst;
    }

    void runScript(const QString& script, const QStringList& args,
                   std::function<void(QString)> onOutput,
                   std::function<void(int)> onFinished);

private slots:
    void processQueue();
    void handleReadyReadStandardOutput();
    void handleFinished(int exitCode);

private:
    PythonRunner();
    QQueue<PythonJob> queue_;
    QProcess* currentProcesses_[3];
    int activeProcesses_ = 0;
};

}
