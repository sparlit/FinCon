#include "PythonRunner.h"
#include "core/Logger.h"

namespace FinConServices {

FinConPythonRunner::FinConPythonRunner() {
    for (int i = 0; i < 3; ++i) currentProcesses_[i] = nullptr;
}

void FinConPythonRunner::runScript(const QString& script, const QStringList& args,
                             std::function<void(QString)> onOutput,
                             std::function<void(int)> onFinished) {
    queue_.enqueue({script, args, onOutput, onFinished});
    processQueue();
}

void FinConPythonRunner::processQueue() {
    if (queue_.isEmpty() || activeProcesses_ >= 3) return;

    for (int i = 0; i < 3; ++i) {
        if (currentProcesses_[i] == nullptr) {
            FinConPythonJob job = queue_.dequeue();
            QProcess* proc = new QProcess(this);
            currentProcesses_[i] = proc;
            activeProcesses_++;

            connect(proc, &QProcess::readyReadStandardOutput, this, [this, i, job]() {
                QString out = currentProcesses_[i]->readAllStandardOutput();
                if (job.onOutput) job.onOutput(out);
            });

            connect(proc, &QProcess::finished, this, [this, i, job](int exitCode) {
                if (job.onFinished) job.onFinished(exitCode);
                currentProcesses_[i]->deleteLater();
                currentProcesses_[i] = nullptr;
                activeProcesses_--;
                processQueue();
            });

            proc->start("python3", QStringList() << "-c" << job.script << job.args);
            break;
        }
    }
}

}
