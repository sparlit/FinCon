#pragma once
#include <QObject>
#include <QProcess>
#include <QQueue>
#include <functional>

namespace FinConServices {

struct FinConPythonJob {
    QString script;
    QStringList args;
    std::function<void(QString)> onOutput;
    std::function<void(int)> onFinished;
    int timeoutMs = 30000;
};

class FinConPythonRunner : public QObject {
    Q_OBJECT
public:
    static FinConPythonRunner& instance() {
        static FinConPythonRunner inst;
        return inst;
    }

    void runScript(const QString& script, const QStringList& args,
                   std::function<void(QString)> onOutput,
                   std::function<void(int)> onFinished,
                   int timeoutMs = 30000);

private slots:
    void processQueue();

private:
    FinConPythonRunner();
    QQueue<FinConPythonJob> queue_;
    QProcess* currentProcesses_[3];
    int activeProcesses_ = 0;
};

}
