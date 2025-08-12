interface SubHeadlineProps {
    headline: string;
    id?: string;
}

export default function SubHeadLine({ headline, id }: SubHeadlineProps) {
    return (
        <h2 id={id} className="mt-16 mb-8 underline underline-offset-8 font-medium decoration-neutral-700/50 text-2xl">{headline}</h2>
    );
};