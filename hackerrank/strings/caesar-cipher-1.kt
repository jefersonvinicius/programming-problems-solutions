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
 * Complete the 'caesarCipher' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER k
 */


const val START_LOWER_ASCII = 97
const val FINAL_LOWER_ASCII = 122

const val START_UPPER_ASCII = 65
const val FINAL_UPPER_ASCII = 90

const val ALPHABET_SIZE = 26

fun getCharCiphered(c: Char, rotateValue: Int) : Char {
    if (c.isUpperCase()) {
        var ciphered = (c.toInt() - START_UPPER_ASCII) + rotateValue;
        return ((ciphered % ALPHABET_SIZE) + START_UPPER_ASCII).toChar()
    }

    var ciphered = (c.toInt() - START_LOWER_ASCII) + rotateValue;
    return ((ciphered % ALPHABET_SIZE) + START_LOWER_ASCII).toChar()
}

fun caesarCipher(s: String, k: Int): String {
    val stringBuilder = StringBuilder()

    for (i in s.indices) {
        if (s[i].isLetter()) {
            stringBuilder.append(getCharCiphered(s[i], k));
        } else {
            stringBuilder.append(s[i]);
        }
    }

    return stringBuilder.toString()
}

fun main(args: Array<String>) {
    val n = readLine()!!.trim().toInt()
    val s = readLine()!!
    val k = readLine()!!.trim().toInt()

    val result = caesarCipher(s, k)

    println(result)
}
