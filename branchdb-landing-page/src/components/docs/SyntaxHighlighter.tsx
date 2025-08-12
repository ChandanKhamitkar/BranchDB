'use client';

import { useEffect } from "react";
import hljs from "highlight.js";
import "highlight.js/styles/vs2015.css";

interface CodeSnippetProps {
  code: string;
  language?: string;
}

const SyntaxHighlighter: React.FC<CodeSnippetProps> = ({ code, language = "javascript" }) => {
  useEffect(() => {
    hljs.highlightAll();
  }, [code]);

  return (
    <pre className="rounded-lg overflow-x-auto bg-[#1e1e1e]  shadow-lg">
      <code className={`language-${language} hljs`}>
        {code}
      </code>
    </pre>
  );
};

export default SyntaxHighlighter;