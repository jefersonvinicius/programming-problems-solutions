import java.io.*
import java.util.*

interface ITextEditorCommandUndoable {
    var result: String;
    fun execute(): String
    fun undo(): String
}

class AppendCommand(initialStr: String, strToAppend: String) : ITextEditorCommandUndoable {
    override var result = initialStr;
    private var strToAppend = strToAppend;

    override fun execute(): String {
        result += strToAppend
        return result;
    }

    override fun undo(): String {
        result = result.subSequence(0, result.length - strToAppend.length).toString()
        return result
    }
}

class DeleteCommand(initialStr: String, numberOfDeletes: Int): ITextEditorCommandUndoable {
    override var result = initialStr;
    private var numberOfDeletes = numberOfDeletes;
    private var caractersDeleted = ""

    override fun execute(): String {
        caractersDeleted = result.subSequence(result.length - numberOfDeletes, result.length).toString()
        result = result.subSequence(0, result.length - numberOfDeletes).toString()
        return result
    }

    override fun undo(): String {
        result += caractersDeleted;
        return result
    }
}

class CommandsHistory {
    var history = mutableListOf<ITextEditorCommandUndoable>()

    fun add(command: ITextEditorCommandUndoable) {
        history.add(command)
    }

    fun getLastCommandAndRemoveIt(): ITextEditorCommandUndoable {
        val command = history.last()
        history.removeAt(history.lastIndex)
        return command
    }
}

fun main(args: Array<String>) {
    val scan = Scanner(System.`in`)
    val n = scan.nextLine().trim().toInt()

    var currentText = ""
    val history = CommandsHistory()
    for (i in 0..n - 1) {
        val operation = scan.nextLine()

        if (operation[0] == '1') {
            val strToAppend = operation.split(" ")[1]
            val command = AppendCommand(currentText, strToAppend)
            currentText = command.execute()
            history.add(command)
        } else if (operation[0] == '2') {
            val numberOfDeletes = operation.split(" ")[1].toInt()
            val command = DeleteCommand(currentText, numberOfDeletes)
            currentText = command.execute()
            history.add(command)
        } else if (operation[0] == '3') {
            val index = operation.split(" ")[1].toInt() - 1
            println(currentText[index])
        } else if (operation[0] == '4') {
            val command = history.getLastCommandAndRemoveIt()
            currentText = command.undo()
        }
    }
}