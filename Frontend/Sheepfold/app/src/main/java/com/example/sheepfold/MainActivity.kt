package com.example.sheepfold

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.sheepfold.ui.theme.SheepfoldTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            val constraints = ConstraintSet{
                val emailText = createRefFor("email_text")
                val emailField = createRefFor("email_field")

                val passwordText = createRefFor("password_text")
                val passwordField = createRefFor("password_field")
                val hidePasswordBtn = createRefFor("hide_btn")

                constrain(emailText){
                    top.linkTo(parent.top)
                    start.linkTo(parent.start)
                    bottom.linkTo(emailField.bottom)
                }
                constrain(emailField){
                    top.linkTo(parent.top)
                    start.linkTo(passwordText.end)

                }
                constrain(passwordText){
                    top.linkTo(emailField.bottom)
                    bottom.linkTo(passwordField.bottom)
                    start.linkTo(parent.start)
                }
                constrain(passwordField){
                    top.linkTo(emailField.bottom)
                    start.linkTo(passwordText.end)
                    end.linkTo(emailField.end)
                }
                constrain(hidePasswordBtn) {
                    top.linkTo(emailField.bottom)
                    start.linkTo(passwordField.end)
                }
            }
            ConstraintLayout(constraints , modifier = Modifier.fillMaxSize()) {
                Text(modifier = Modifier.layoutId("email_text"),
                    text = "Email")

                TextField(
                    value = "text",
                    modifier = Modifier.layoutId("email_field"),
                    onValueChange = {

                    })


                Text(modifier = Modifier.layoutId("password_text"),
                    text = "Password")

                TextField(
                    value = "text",
                    modifier = Modifier.layoutId("password_field"),
                    onValueChange = {

                    })

                IconButton(
                    modifier = Modifier
                        .clip(RoundedCornerShape(16.dp))
                        .background(Color.Red)
                        .layoutId("hide_btn"),

                    onClick = {}
                ) {
                    Icon(
                        painter = painterResource(R.drawable.baseline_remove_red_eye_24),
                        contentDescription = "Delete",
                        tint = Color.White
                    )
                }

            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    SheepfoldTheme {
        Greeting("Android")
    }
}