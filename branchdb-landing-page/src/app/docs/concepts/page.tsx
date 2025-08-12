import CodeBlock from "@/components/docs/CodeBlock";
import SubHeadLine from "@/components/docs/SubHeadLine";
import Line from "@/components/docs/Line";
import DocsLayout from "../DocsLayout";
import Point from "@/components/docs/Point";
import CommandsTable from "@/components/docs/CommandsTable";
import CodeSnippet from "@/components/docs/CodeSnippet";
import { commandsData, TTLTerminalLines } from "@/lib/docs/concepts/conceptsData";


export default function page() {
    return (
        <DocsLayout>
            <div className="w-full h-auto flex flex-col justify-start items-start">

                {/* Concepts */}
                <div className="w-full p-4 mt-6">
                    <p className="text-4xl font-bold text-white mb-4">Core Features</p>
                    <Point pt="BranchDB is an in-memory key-value store built in C++, with support for TTL, set operations, authentication, and disk persistence. You can connect via a TCP client on port 1981 to start issuing commands." />

                    <SubHeadLine headline="Commands" />
                    <Point pt="Below is a quick overview of common BranchDB commands, what they do, and their syntax." />

                    <CommandsTable heads={[{ cnt: "Command", gradientMode: true }, { cnt: "Syntax", gradientMode: false }, { cnt: "Description", gradientMode: false }]} data={commandsData} />
                    <SubHeadLine id="ttl" headline="Time To Live" />
                    <Point pt="BranchDB allows you to store keys temporarily using TTL. You can attach an expiry time (in seconds) when setting a key. Once the time is up, the key vanishes — no manual deletion needed." />

                    <CodeSnippet title="Terminal" lines={TTLTerminalLines} />
                </div>
            </div>
        </DocsLayout>
    )
};
