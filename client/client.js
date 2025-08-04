import net from "net";
import readline from "readline";

const HOST = "localhost";
const PORT = 1981;

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: "> ",
});

const client = new net.Socket();

client.on("connect", () => {
  console.log("CLIENT connected to server at ", HOST, " ", PORT);
  console.log("CLIENT Ready to send commands. Type 'exit' to quit.");
  rl.prompt();
});

client.on("data", (data) => {
  const serverResponse = data.toString().trim();
  console.log(`[SERVER] ${serverResponse}`);
  rl.prompt();
});

rl.on("line", (line) => {
  const trimmedLine = line.trim();
  if (trimmedLine.toLowerCase() === "exit") {
    console.log("[CLIENT] Closing connection...");
    client.end();
    rl.close();
  } else {
    client.write(trimmedLine + "\n");
  }
});

client.on("close", () => {
  console.log("CLIENT connection closed.");
});

client.on("error", (err) => {
  console.log("CLIENT error occured: ", err);
  rl.close();
});

client.connect(PORT, HOST, () => {});
