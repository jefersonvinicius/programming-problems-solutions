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

fun superReducedString(s: String): String {
    var result = s;
    while (true) {
        val resultWithAdjacentsLetterRemoved = removeNextDuplicatedAdjacentsLetters(result);

        if (resultWithAdjacentsLetterRemoved == result) break
        else result = resultWithAdjacentsLetterRemoved
    }
    return if (result.length == 0) "Empty String" else result
}

fun removeNextDuplicatedAdjacentsLetters(s: String): String {
    var result = s;
    for (index in 0 until result.length - 1) {
        if (result.get(index) == result.get(index + 1)) {
            return result.removeRange(index, index + 2)
        }
    }
    return result;
}

fun main(args: Array<String>) {
    val s = readLine()!!
    val result = superReducedString(s)
    println(result)
}
