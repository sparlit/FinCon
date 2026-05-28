#include "PythonRunner.h"
#include "core/Logger.h"
#include <QTimer>

namespace FinConServices {

FinConPythonRunner::FinConPythonRunner() {
    for (int i = 0; i < 3; ++i) FinConPython_Processes[i] = nullptr;
}

void FinConPythonRunner::runScript(const QString& script, const QStringList& args,
                             std::function<void(QString)> onOutput,
                             std::function<void(int)> onFinished,
                             int timeoutMs) {
    FinConPython_Queue.enqueue({script, args, onOutput, onFinished, timeoutMs});
    processQueue();
}

void FinConPythonRunner::processQueue() {
    if (FinConPython_Queue.isEmpty() || FinConPython_ActiveCount >= 3) return;

    for (int i = 0; i < 3; ++i) {
        if (FinConPython_Processes[i] == nullptr) {
            FinConPythonJob job = FinConPython_Queue.dequeue();
            QProcess* proc = new QProcess(this);
            FinConPython_Processes[i] = proc;
            FinConPython_ActiveCount++;

            connect(proc, &QProcess::readyReadStandardOutput, this, [this, i, job]() {
                QString out = FinConPython_Processes[i]->readAllStandardOutput();
                if (job.onOutput) job.onOutput(out);
            });

            QTimer::singleShot(job.timeoutMs, proc, [proc, i, this]() {
                if (proc->state() != QProcess::NotRunning) {
                    FINCON_LOG_WARN("Python", "Process timed out. Killing...");
                    proc->kill();
                }
            });

            connect(proc, &QProcess::finished, this, [this, i, job](int exitCode) {
                if (job.onFinished) job.onFinished(exitCode);
                FinConPython_Processes[i]->deleteLater();
                FinConPython_Processes[i] = nullptr;
                FinConPython_ActiveCount--;
                processQueue();
            });

            proc->start("python3", QStringList() << "-" << job.args);
            proc->write(job.script.toUtf8());
            proc->closeWriteChannel();
            break;
        }
    }
}

}
