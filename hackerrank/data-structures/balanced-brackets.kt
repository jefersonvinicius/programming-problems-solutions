import java.io.*
import java.math.*
import java.security.*
import java.text.*
import java.util.*
import java.util.concurrent.*
import java.util.function.*
import java.util.regex.*
import java.util.stream.*
import kotlin.collections.*
import kotlin.comparisons.*
import kotlin.io.*
import kotlin.jvm.*
import kotlin.jvm.functions.*
import kotlin.jvm.internal.*
import kotlin.ranges.*
import kotlin.sequences.*
import kotlin.text.*

fun isBalanced(s: String): String {
    val balanced = mutableListOf<Char>()
    for (i in s.indices) {
        val c = s[i]
        if (c in "{[(") balanced.add(c)
        else if (c == '}' && balanced.lastOrNull() == '{') balanced.removeAt(balanced.lastIndex)
        else if (c == ']' && balanced.lastOrNull() == '[') balanced.removeAt(balanced.lastIndex)
        else if (c == ')' && balanced.lastOrNull() == '(') balanced.removeAt(balanced.lastIndex)
        else return "NO"
    }

    return if (balanced.size == 0) "YES" else "NO"
}

fun main(args: Array<String>) {
    val scan = Scanner(System.`in`)

    val t = scan.nextLine().trim().toInt()

    for (tItr in 1..t) {
        val s = scan.nextLine()

        val result = isBalanced(s)

        println(result)
    }
}
