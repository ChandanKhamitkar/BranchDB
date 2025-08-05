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
  console.log(`\n[RAW DATA] Received ${data.length} bytes:`);
  console.log(`[RAW DATA] Hex: ${data.toString("hex")}`);

  let offset = 0;

  const status_code = data.readInt8(offset);
  offset += 1;

  const success = data.readInt8(offset);
  offset += 1;

  const message_len = data.readUint32LE(offset);
  offset += 4;

  const message = data.toString("utf8", offset, offset + message_len);
  offset += message_len;

  const payload_len = data.readUint32LE(offset);
  offset += 4;

  const payload = data.toString("utf8", offset, offset + payload_len);
  offset += payload_len;

  const response = {
    statusCode: status_code,
    success: success,
    message: message,
    payload: payload,
  };

  console.log(`[PARSED] Received Response:`, response);

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
