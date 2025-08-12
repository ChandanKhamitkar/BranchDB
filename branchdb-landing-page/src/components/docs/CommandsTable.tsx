import React from 'react';

interface CommandTableProps {
    heads: HeadsProps[];
    data: Command[]
}

interface HeadsProps {
    gradientMode: boolean;
    cnt: string
}

interface Command {
    command?: string;
    syntax?: string;
    description?: string;
}


const CommandsTable = (props: CommandTableProps) => {
    return (
        <div className="relative overflow-x-auto shadow-lg sm:rounded-lg">
            <table className="w-full text-sm text-left text-white">
                <thead className="text-lg bg-neutral-800">
                    <tr>
                        {
                            props.heads.map((item, index) => <th key={index} scope="col" className={`border border-neutral-700 px-4 py-3 ${item.gradientMode && "bg-gradient-to-r from-primarylight to-primary text-transparent bg-clip-text"} `}>
                                {item.cnt}
                            </th>)
                        }
                    </tr>
                </thead>
                <tbody>
                    {props.data.map((cmd, index) => (
                        <tr
                            key={index}
                            className={`bg-neutral-900 border border-neutral-700 hover:bg-neutral-600/50 transition-colors duration-200`}
                        >
                            {
                                cmd.command && <th className="px-6 py-4 text-md font-medium text-gray-200 whitespace-nowrap border border-neutral-700">
                                    {cmd.command}
                                </th>
                            }
                            {
                                cmd.syntax && <td className="px-6 py-4 font-mono text-white border border-neutral-700">
                                    <code className="bg-neutral-700 p-1 rounded-sm">{cmd.syntax}</code>
                                </td>
                            }
                            {
                                cmd.description && <td className="px-6 py-4 border border-neutral-700">
                                    {cmd.description}
                                </td>
                            }
                        </tr>
                    ))}
                </tbody>
            </table>
        </div>
    );
};

export default CommandsTable;