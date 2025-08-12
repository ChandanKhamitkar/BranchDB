
export default function Point({ pt, customStyling }: { pt: string, customStyling?: string }) {
    return (
        <p className={`text-neutral-400 mb-2 ${customStyling}`}>{pt}</p>
    );
};