import { MdContentCopy } from "react-icons/md";

interface TerminalPart {
    text: string;
    color?: string;
}

interface TerminalLine {
    parts: TerminalPart[];
    className?: string;
}

export interface CodeSnippetProps {
    title: string;
    lines: TerminalLine[];
}

const CodeSnippet = (props: CodeSnippetProps) => {
    return (
        <div className="min-w-[40%] max-w-[80%] w-fit h-auto px-1 pt-2 pb-1 bg-neutral-900 flex flex-col justify-start items-center rounded-t-lg rounded-b-md">

            {/* Header */}
            <div className="w-full text-neutral-400 flex justify-between items-center px-2 mb-2 rounded-t-3xl">
                <p className="text-md">{props.title}</p>
                <MdContentCopy />
            </div>

            {/* Body */}
            <div className="w-full flex flex-col gap-2 justify-start bg-black rounded-md px-3 py-4 font-mono">
                {props.lines.map((line, i) => (
                    <p key={i} className={`${line.className || ""} whitespace-pre`}>
                        {line.parts?.map((part, j) => (
                            <span key={j} className={`${part.color || ""} whitespace-pre`}>
                                {part.text}
                            </span>
                        ))}
                    </p>
                ))}
            </div>
        </div>
    );
};

export default CodeSnippet;