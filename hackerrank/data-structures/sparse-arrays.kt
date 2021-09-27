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

fun matchingStrings(strings: Array<String>, queries: Array<String>): Array<Int> {
    val stringAmounts: MutableMap<String, Int> = mutableMapOf()
    for (string in strings) {
        stringAmounts[string] = stringAmounts.getOrDefault(string, 0) + 1
    }

    val result = mutableListOf<Int>()
    for (query in queries) {
        result.add(stringAmounts.getOrDefault(query, 0))
    }

    return result.toTypedArray()
}

fun main(args: Array<String>) {
    val stringsCount = readLine()!!.trim().toInt()

    val strings = Array<String>(stringsCount, { "" })
    for (i in 0 until stringsCount) {
        val stringsItem = readLine()!!
        strings[i] = stringsItem
    }

    val queriesCount = readLine()!!.trim().toInt()

    val queries = Array<String>(queriesCount, { "" })
    for (i in 0 until queriesCount) {
        val queriesItem = readLine()!!
        queries[i] = queriesItem
    }

    val res = matchingStrings(strings, queries)

    println(res.joinToString("\n"))
}
