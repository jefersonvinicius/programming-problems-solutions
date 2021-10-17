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

/*
 * Complete the 'checkMagazine' function below.
 *
 * The function accepts following parameters:
 *  1. STRING_ARRAY magazine
 *  2. STRING_ARRAY note
 */

fun checkMagazine(magazine: Array<String>, note: Array<String>): Unit {
    var isPossibleWrite = true

    val magazineDictionary = mutableMapOf<String, Int>()
    for (magazineWord in magazine) {
        val wordAmount = magazineDictionary.getOrDefault(magazineWord, 0) + 1
        magazineDictionary.put(magazineWord, wordAmount)
    }

    for (noteWord in note) {
        val wordAmount = magazineDictionary.getOrDefault(noteWord, 0)
        if (wordAmount > 0) {
            magazineDictionary.put(noteWord, wordAmount - 1)
        } else {
            isPossibleWrite = false;
            break;
        }
    }

    println(if (isPossibleWrite) "Yes" else "No")
}

fun main(args: Array<String>) {
    val first_multiple_input = readLine()!!.trimEnd().split(" ")

    val m = first_multiple_input[0].toInt()

    val n = first_multiple_input[1].toInt()

    val magazine = readLine()!!.trimEnd().split(" ").toTypedArray()

    val note = readLine()!!.trimEnd().split(" ").toTypedArray()

    checkMagazine(magazine, note)
}
